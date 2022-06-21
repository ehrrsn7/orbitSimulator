/**********************************************************************
 * simulator.h
 * orbitSimulator 
 *
 * Summary:
 *    The class that contains the update, handleInput and display methods
 *    and handles all the Sim logic.
 **********************************************************************/

#pragma once

#include "earth.h"
#include "movingObject.h"
#include "star.h"
#include "uiInteract.h"
#include "uiDraw.h"

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#include <vector>


/**************************************************
 * CLASS Simulator
 *    Orbit Simulator
 *    This class will handle all the logic for all
 *    the objects and movement in our simulator
 **************************************************/
class Simulator {
    
public:
   Simulator(Position ptUpperRight) : tr(ptUpperRight), dt(0.0) {
      // earth -- nothing needed
      // ship
      ship.setPosition(Position(10000000, 10000000));
      ship.setVelocity(Velocity(500000, 500000));
      // stars
      // satellites
      /// sputnik
      Sputnik* sputnik = new Sputnik; // allocate new memory
      sputnik->setPosition(Position(-36515095.13, 21082000.0)); // m
      sputnik->setVelocity(Velocity(2050.0, 2684.68)); // m/s
      satellites.push_back(sputnik);
      /// GPS
      createGPSObjects();
      // fragments
      // projectiles
   }
    
   void update() {
      // self
      handleCollisions();
      applyGravity();
      cleanUpZombies();
      
      // duck duck goose
      if (earth.isAlive()) earth.update();
      if (ship.isAlive()) ship.update();
      for (auto it : stars) it.update();
      for (auto it : satellites)    if (it->isAlive()) it->update();
      for (auto it : fragments)     if (it.isAlive())  it.update();
      for (auto it : projectiles)   if (it.isAlive())  it.update();
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
      dt = pUI->getDeltaTime();
      std::cout << dt*1000 << " ms\n";
      if (pUI->isEscape()) exit(0); // press ESC to end program

      // do our rounds..
      if (earth.isAlive()) earth.handleInput(pUI);
      if (ship.isAlive()) ship.handleInput(pUI);
      for (auto it : stars) it.handleInput(pUI);
      for (auto it : satellites)  if (it->isAlive()) it->handleInput(pUI);
      for (auto it : fragments)   if (it.isAlive())  it.handleInput(pUI);
      for (auto it : projectiles) if (it.isAlive())  it.handleInput(pUI);
   }
   

private:
   // Screen Dimensions
   Position tr; // upper-right point of window
   // (center is [0,0], giving us dimensions w/2 and h/2)
   
   // time
   double dt;
   
   // objects on the screen
   Earth earth;
   Ship ship;
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
         for (auto it : satellites)  if (it->isAlive()) handleCollision(ship, *it);
         for (auto it : fragments)   if (it.isAlive())  handleCollision(ship, it);
         for (auto it : projectiles) if (it.isAlive())  handleCollision(ship, it);
         
         // ship and earth
         if (earth.isAlive()) ship.hit();
         
         // ship and edge of screen
         if (abs(ship.getPosition().getX()) >= tr.getX() || abs(ship.getPosition().getY()) >= tr.getY()) ship.hit();
      }
      
      // bullets and moving objects
   }
   
   void handleCollision(MovingObject & obj1, MovingObject & obj2) {
      if (computeDistance(obj1.getPosition(), obj2.getPosition()) < obj1.getRadius() + obj2.getRadius()) {
         obj1.hit();
         obj2.hit();
      }
   }
   
   void applyGravity() {
      // earth -> moving objects
      if (ship.isAlive()) ship.applyGravity(earth, dt);
      for (auto it : satellites)  if (it->isAlive()) it->applyGravity(earth, dt);
      for (auto it : fragments)   if (it.isAlive())  it.applyGravity(earth, dt);
      for (auto it : projectiles) if (it.isAlive())  it.applyGravity(earth, dt);
      
      // moving objects -> earth lol
      
      // moving objects to each other HAHAHA
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
};
