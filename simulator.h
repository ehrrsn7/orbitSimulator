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
      ship.setPosition(Position(10000000, 10000000));
   }
    
   void update() {
      // self
      handleCollisions();
      
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
      for (auto it : satellites) if (it->isAlive()) it->display();
      for (auto it : fragments) if (it.isAlive()) it.display();
      for (auto it : projectiles) if (it.isAlive()) it.display();
   }
 
   void handleInput(const Interface * pUI) {
      // self
      if (pUI->isEscape()) exit(0); // press ESC to end program

      // do our rounds..
      if (earth.isAlive()) earth.handleInput(pUI);
      if (ship.isAlive()) ship.handleInput(pUI);
      for (auto it : stars) it.handleInput(pUI);
      for (auto it : satellites) if (it->isAlive()) it->handleInput(pUI);
      for (auto it : fragments) if (it.isAlive()) it.handleInput(pUI);
      for (auto it : projectiles) if (it.isAlive()) it.handleInput(pUI);
   }
   

private:
   // Screen Dimensions
   Position tr; // upper-right point of window
   // (center is [0,0], giving us dimensions w/2 and h/2)
   
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
      if (earth.isAlive()) earth.display();
      if (ship.isAlive()) ship.display();
      for (auto it : stars) it.display();
      for (auto it : satellites) if (it->isAlive()) it->display();
      for (auto it : fragments) if (it.isAlive()) it.display();
      for (auto it : projectiles) if (it.isAlive()) it.display();
      
      // moving objects -> earth lol
      
      // moving objects to each other HAHAHA
   }
   
   void cleanUpZombies() {
      // all vector<MovingObject> contents
      for (auto it : satellites) if (!it->isAlive()) ;
      for (auto it : fragments) if (!it.isAlive())  ;
      for (auto it : projectiles) if (!it.isAlive())  ;
   }
};
