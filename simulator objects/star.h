/**********************************************************************
 * star.h
 * orbitSimulator
 **********************************************************************/

#pragma once

#include "uiInteract.h"
#include "uiDraw.h"

/**************************************************
 * CLASS Star
 *    Simple class definition for the stars to be
 *    drawn on the screen in the background.
 **************************************************/
class Star {
public:
   Star() {}
   Star(Position p) : p(p) {}
   
   void update() { }
   void display() const { }
   void handleInput(const Interface * pUI) { }

private:
   Position p;
   double phase;
   
   /**************************************************
    * helper methods
    **************************************************/
   void twinkle() {
      // update phase
      
   }
};
