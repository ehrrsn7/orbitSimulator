/***********************************************************************
 * Heaader File:
 *    Simulator class
 *
 * Summary:
 *    The class that contains the update, handleInput and display methods
 *    and handles all the Sim logic.
 ************************************************************************/


#pragma once

#include "earth.h"
#include "geostationarySatellite.h"
#include "uiInteract.h"
#include "uiDraw.h"

class Simulator {
    
public:
   Simulator(Position ptUpperRight) : tr(ptUpperRight), bob(tr) { }
    
   void update(const Interface * pUI) {
      bob.setRelativePosition(earth.getAngle());
      
      earth.update(pUI); // Earth
      bob.update(pUI); // Geostationary Satellite
   }
    
   void display() const {
      // hello operator, I'd like to call...
      earth.display();
      bob.display();
   }
 
   void handleInput(const Interface * pUI) {
      earth.handleInput(pUI);
      bob.handleInput(pUI);
      if (pUI->isEscape()) exit(0);
   }
 
private:
   // screen
   Position tr; // upper-right point of window (center is [0,0] so this gives us dimensions w/2 and h/2)
   
   // Earth
   Earth earth;
   
   // MovingObjects
   GeostationarySatellite bob;
};
