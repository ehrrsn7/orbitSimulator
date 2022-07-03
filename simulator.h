/**********************************************************************
 * simulator.h
 * orbitSimulator 
 *
 * Summary:
 *    The class that contains the update, handleInput and display methods
 *    and handles all the Sim logic.
 **********************************************************************/

#pragma once

#include "earth.h" // import this before MovingObject
#include "movingObject.h"
#include "satellite.h"
#include "ship.h"
#include "star.h"
#include "uiInteract.h"
#include "uiDraw.h"

#include <vector>

/**************************************************
 * CLASS Simulator
 *    Orbit Simulator
 *    This class will handle all the logic for all
 *    the objects and movement in our simulator
 **************************************************/
class Simulator {
    
public:
   Simulator(Position ptUpperRight) : tr(ptUpperRight) {
      // Earth -- nothing needed

      // Ship -- nothing needed

      // Stars[]
      unsigned int starAmount = 300;
      for (int i = 0; i < starAmount; i++)
         stars.push_back(Star(randomPositionOnScreen()));

      // Satellites[]
      /// Sputnik
      Sputnik* sputnik = new Sputnik; // allocate new memory
      satellites.push_back(sputnik);
      
      /// GPS (x5)
      createGPSObjects();
      
      /// Hubble
      Hubble* hubble = new Hubble; // allocate new memory
      satellites.push_back(hubble);
      
      /// SpaceX Crew Dragon
      CrewDragon* crewDragon = new CrewDragon; // "
      satellites.push_back(crewDragon);
      
      /// SpaceX Starlink
      Starlink* starlink = new Starlink;
      satellites.push_back(starlink);
      
      /// Broken Satellite Pieces (child of Satellite) -- none at construction
      ///
      /// test:
//      Satellite* satPtr = satellites[0];
//      auto newFragments = satPtr->breakIntoFragments(); // TODO: fix and verify that len(newFragments) == 4, not 0
      
      // fragments[] -- none at construction
      
      // projectiles[] -- none at construction
      
      // test split
      auto parts = satellites[1]->breakIntoParts();
      for (auto it : parts) std::cout << it.getPosition() << std::endl;
   }
    
   void update(const Interface * pUI) {
      // self
      handleCollisions();
      applyGravity(pUI);
      cleanUpZombies();
      
      // duck duck goose
      if (earth.isAlive()) earth.update(pUI);
      if (ship.isAlive()) ship.update(pUI);
      
      for (auto it = stars.begin(); it != stars.end(); ++it)
         it->update();
      
      for (auto it = satellites.begin(); it != satellites.end(); ++it)
         if ((*it)->isAlive())
            (*it)->update(pUI);
      
      for (auto it = fragments.begin(); it != fragments.end(); ++it)
         if (it->isAlive())
            it->update(pUI);
      
      for (auto it = projectiles.begin(); it != projectiles.end(); ++it)
         if (it->isAlive())
            it->update(pUI);
   }
    
   void display() const {
      // self
      
      // hello operator, I'd like to call...
      if (earth.isAlive()) earth.display();
      if (ship.isAlive()) ship.display();
      for (auto it : stars) it.display();
      for (auto it : satellites)  if (it->isAlive()) it->display();
      for (auto it : fragments)   if (it.isAlive())  it.display();
      for (auto it : projectiles) if (it.isAlive())  it.display();
   }
 
   void handleInput(const Interface * pUI) {
      // self
      if (pUI->isSpace()) {
         if (ship.timeToFireProjectile()) {
            auto newProjectile = ship.fire();
            projectiles.push_back(newProjectile);
         }
      }

      // do our rounds..
      if (earth.isAlive()) earth.handleInput(pUI);
      // if (ship.isAlive()) ship.handleInput(pUI);
      ship.handleInput(pUI);
      for (auto it : stars) it.handleInput(pUI);
      for (auto it : satellites)  if (it->isAlive()) it->handleInput(pUI);
      for (auto it : fragments)   if (it.isAlive())  it.handleInput(pUI);
      for (auto it : projectiles) if (it.isAlive())  it.handleInput(pUI);
   }


private:
   // Screen Dimensions
   Position tr; // upper-right point of window
   // (center is [0,0], giving us dimensions w/2 and h/2)
   
   // objects on the screen
   Earth earth;
   SpaceShip ship;
   std::vector<Satellite*> satellites; // pointers* for polymorphism
   std::vector<Fragment> fragments;
   std::vector<Projectile> projectiles;
   std::vector<Star> stars;
   
   /**************************************************
    * helper methods
    **************************************************/
   void handleCollisions() {
      // ship and other
      if (ship.isAlive()) {
         
         // ship and smaller objects
         for (auto it : satellites)  if (it->isAlive() && handleCollision(ship, *it))
         {
            ship.hit();
            it->hit();
         }
         for (auto it : fragments)   if (it.isAlive() && handleCollision(ship, it))
         {
            ship.hit();
            it.hit();
         }
         
         // ship and earth
         if (handleCollision(ship, earth)) ship.hit();
         
         // ship and edge of screen
         if (abs(ship.getPosition().getX()) >= tr.getX() || abs(ship.getPosition().getY()) >= tr.getY()) ship.hit();
      }
      // everything to the earth
      for (auto it : satellites)  if (it->isAlive() && handleCollision(earth, *it)) {it->hit();}
      for (auto it : fragments)   if (it.isAlive() && handleCollision(earth, it))   {it.hit();}
      for (auto it : projectiles) if (it.isAlive() && handleCollision(earth, it))   {it.hit();}
      
      // bullets and moving objects
   }
   
   bool handleCollision(MovingObject & obj1, MovingObject & obj2) {
      return (computeDistance(obj1.getPosition(), obj2.getPosition()) < obj1.getRadius() + obj2.getRadius());
   }
   
   void applyGravity(const Interface * pUI) {
      if (ship.isAlive())
         ship.applyGravity(earth, pUI->getDeltaTime());
      
      for (auto it : satellites)
         if (it->isAlive())
            it->applyGravity(earth, pUI->getDeltaTime());
      
      for (auto it : fragments)
         if (it.isAlive())
            it.applyGravity(earth, pUI->getDeltaTime());
      
      for (auto it : projectiles)
         if (it.isAlive())
            it.applyGravity(earth, pUI->getDeltaTime());
   }
   
   void cleanUpZombies() {
      // clean up all dead satellites
      std::vector<Satellite*>::iterator sIt = satellites.begin();
      while (sIt != satellites.end()) {
         if (!(*sIt)->isAlive()) {
            
            // unallocate memory
            Satellite* pSIt = *sIt;
            delete pSIt;
            pSIt = NULL;
            
            // remove from vector and iterate
            sIt = satellites.erase(sIt);
         }
         // just keep swimming
         else ++sIt;
      }
      
      // clean up all dead fragments
      std::vector<Fragment>::iterator fIt = fragments.begin();
      while (fIt != fragments.end()) {
         if (!fIt->isAlive())
            fIt = fragments.erase(fIt);
         else ++fIt;
      }
      
      // clean up all dead projectiles
      std::vector<Projectile>::iterator pIt = projectiles.begin();
      while (pIt != projectiles.end()) {
         if (!pIt->isAlive())
            pIt = projectiles.erase(pIt);
         else ++pIt;
      }
   }
   
   void deleteAllSatellites() {
      // idk why you'd need this helper function but it's
      // a great reference for how to correctly unallocate
      // the memory of pointers (they don't fall in the same
      // scope of memory as the other attributes/class variables)
      
      // check to see if there are any satellites left
      // (just check position 0, this will do.)
      if (satellites[0] != NULL) {
         
         // create a Satellite* iterator, set it to point to
         // the first position in satellites
         std::vector<Satellite*>::iterator it = satellites.begin();
         
         while (it != satellites.end()) {
            // normally here we'd increment by calling ++it,
            // but vector::erase will move us through each
            // item in the collection to the end
            
            // dereference the iterator object using * to get the Satellite* pointer
            Satellite* satellite_ptr = *it; // referring to this as (*it) works just fine
            
            // now we have our pointer, which we want to delete:
            if (satellite_ptr != NULL) { // this should always be null
               
               // The first necessary step before we remove the object + its pntr
               // is to delete the object and set its pointer to NULL
               delete satellite_ptr;
               satellite_ptr = NULL;
               
            }
            
            // the next necessary step in removing an object + pntr
            // is to remove its pointer (now NULL) from vector
            it = satellites.erase(it);
            
         }
      }
      
      // "only YOU can prevent memory leaks!" ("please allocate responsibly")
   }
   
   // helper methods

   Satellite* createGPSObject(Position p, Velocity v) {
      GPS* newGPS = new GPS; // allocate new memory
      newGPS->setPosition(p); // m
      newGPS->setVelocity(v); // m/s
      return newGPS;
   }

   void createGPSObjects() {
      Position initialP;
      Velocity initialV;

      // ( 0.0 m, 26,560,000.0 m) (-3,880.0 m/s, 0.0 m/s)
      initialP.set(0.0, 26560000.0);
      initialV.set(-3880.0, 0.0);
      satellites.push_back(createGPSObject(initialP, initialV));

      // ( 23,001,634.72 m, 13,280,000.0 m) ( -1,940.00 m/s, 3,360.18 m/s)
      initialP.set(23001634.72, 13280000.0);
      initialV.set(-1940.00, 3360.18);
      satellites.push_back(createGPSObject(initialP, initialV));

      // ( 0.0 m, -26,560,000.0 m) ( 3,880.0 m/s, 0.0 m/s)
      initialP.set(0.0, -26560000.0);
      initialV.set(3880.0, 0.0);
      satellites.push_back(createGPSObject(initialP, initialV));

      // (023,001,634.72 m, -13,280,000.0 m)	( 1,940.00 m/s, -3,360.18 m/s)
      initialP.set(023001634.72, -13280000.0);
      initialV.set(1940.00, -3360.18);
      satellites.push_back(createGPSObject(initialP, initialV));

      // (-23,001,634.72 m, 13,280,000.0 m) ( -1,940.00 m/s, -3,360.18 m/s)
      initialP.set(-23001634.72, -13280000.0);
      initialV.set(-1940.00, -3360.18);
      satellites.push_back(createGPSObject(initialP, initialV));
   }
   
   Position randomPositionOnScreen() const {
      Position p;
      while (distance(p, earth.getPosition()) < earth.getRadius())
         p.set(random(-tr.getMetersX(), tr.getMetersX()),
               random(-tr.getMetersY(), tr.getMetersY()));
      return p;
   }
};

// helper function for callback(): if we want to restart our program in-game
void replaceSimulator(Position tr, Simulator* pSim) {
   Simulator* newSimulator = new Simulator(tr);
   delete pSim; // don't forget to free old memory!
   pSim = newSimulator; // the ol switcheroo
}
