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
   Simulator(Position ptUpperRight) : tr(ptUpperRight) { }
    
   void update(const Interface * pUI) {
      // self
      
      // duck duck goose
      earth.update(); // Earth
      ship.update(); // Ship
   }
    
   void display() const {
      // self
      
      // hello operator, I'd like to call...
      earth.display();
   }
 
   void handleInput(const Interface * pUI) {
      // self
      if (pUI->isEscape()) exit(0);

      // do our rounds..
      earth.handleInput(pUI);
   }
   
   /*
    + Constructor/lnitializer()
    + Constructor/Initializer(tr : P.)
    + update()
    + display()
    + handlelnput(pUI)
    - handleCollisions()
    - applyGravity()
    - cleanUpZombies()
    
    */

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
};
