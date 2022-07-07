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
   Star(): phase(random(0, 255)) { }
   Star(Position p) : p(p), phase(random(0, 255)) { }
   
   void update() {
      phase += 1;
      twinkle();
   }
   
   void display() const {
      drawStar(p, phase);
   }
   
   void handleInput(const Interface * pUI) { }

private:
   Position p;
   unsigned char phase;
   
   /**************************************************
    * helper methods
    **************************************************/
   void twinkle() {
      // update phase once per frame
      phase++;
   }
};
