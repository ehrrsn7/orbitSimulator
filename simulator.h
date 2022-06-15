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
#include "geostationarySatellite.h"
#include "uiInteract.h"
#include "uiDraw.h"

/**************************************************
 * CLASS Simulator
 *    Orbit Simulator
 *    This class will handle all the logic for all
 *    the objects and movement in our simulator
 **************************************************/
class Simulator {
    
public:
   Simulator(Position ptUpperRight) : tr(ptUpperRight), bob(tr) { }
    
   void update(const Interface * pUI) {
      // self
      bob.setRelativePosition(earth.getAngle());
      
      // duck duck goose
      earth.update(pUI); // Earth
      bob.update(pUI); // Geostationary Satellite
   }
    
   void display() const {
      // self
      
      // hello operator, I'd like to call...
      earth.display();
      bob.display();
   }
 
   void handleInput(const Interface * pUI) {
      // self
      if (pUI->isEscape()) exit(0);

      // do our rounds..
      earth.handleInput(pUI);
      bob.handleInput(pUI);
   }
 
private:
   // screen
   Position tr; // upper-right point of window
   // (center is [0,0] giving us dimensions w/2 and h/2)
   
   // Earth
   Earth earth;
   
   // MovingObjects
   GeostationarySatellite bob;
};
