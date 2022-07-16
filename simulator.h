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
      
      /// Broken Satellite Pieces (part of satellites[]) -- none at construction
      /// Fragments (part of satellites[]) -- none at construction
//      Fragment * frag = new Fragment(Position(10000, 10000), Velocity(0,0), 0.0);
//      satellites.push_back(frag);
      
      // projectiles[] -- none at construction
   }
   
   ~Simulator() {
      deleteAllSatellites();
   }
    
   void update(const Interface * pUI) {
      // duck duck goose
      if (earth.isAlive()) earth.update(pUI);
      if (ship.isAlive()) ship.update(pUI);
      
      for (auto it = stars.begin(); it != stars.end(); ++it)
         it->update();
      
      for (auto it = satellites.begin(); it != satellites.end(); ++it)
         if ((*it)->isAlive())
            (*it)->update(pUI);
      
      for (auto it = projectiles.begin(); it != projectiles.end(); ++it)
         if (it->isAlive())
            it->update(pUI);
      
      // self
      handleCollisions();
      applyGravity(pUI);
      cleanUpZombies();
   }
    
   void display() const {
      // self
      
      // hello operator, I'd like to call...
      if (earth.isAlive()) earth.display();
      if (ship.isAlive()) ship.display();
      for (auto it : stars) it.display();
      for (auto it : satellites)  if (it->isAlive()) it->display();
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
      
      // statics
      if (pUI->isB()) MovingObject::toggleShowHitboxes();

      // do our rounds..
      if (earth.isAlive()) earth.handleInput(pUI);
      if (ship.isAlive()) ship.handleInput(pUI);
      for (auto it : stars) it.handleInput(pUI);
      for (auto it : satellites)  if (it->isAlive()) it->handleInput(pUI);
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
   std::vector<Projectile> projectiles;
   std::vector<Star> stars;
   
   /**************************************************
    * helper methods
    **************************************************/

   // handle collisions
   void handleCollisions();
   
   // handle collision overrides
   void handleCollision(SpaceShip, Earth);
   void handleCollision(Earth, Projectile & projectile);
   void handleCollision(Earth, Satellite * satellite);
   void handleCollision(SpaceShip, Satellite* satellite);
   void handleCollision(Projectile & projectile, Satellite * satellite);
   
   void applyGravity(const Interface * pUI);
   
   // remove all objects where obj.isAlive() == false
   void cleanUpZombies();
   void cleanUpSatellites();
   void cleanUpProjectiles();
   
   // miscellaneous
   void deleteAllSatellites();
   Satellite* createGPSObject(Position p, Velocity v);
   void createGPSObjects();
   Position randomPositionOnScreen() const;
   
   std::string getSatelliteName(const Satellite * s) {
      if (typeid(*s) == typeid(SatellitePart))  return "SatellitePart"; // change to SatellitePart AND children classes
      if (typeid(*s) == typeid(Sputnik))        return "Sputnik";
      if (typeid(*s) == typeid(GPS))            return "GPS";
      if (typeid(*s) == typeid(Hubble))         return "Hubble";
      if (typeid(*s) == typeid(CrewDragon))     return "CrewDragon";
      if (typeid(*s) == typeid(Starlink))       return "Starlink";
      if (typeid(*s) == typeid(Fragment))       return "Fragment";
      else                                      return "unknown";
   }

};

// helper function for callback(): if we want to restart our program in-game
void replaceSimulator(Position tr, Simulator* pSim);
