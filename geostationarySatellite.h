/***********************************************************************
 * geostationarySatellite.h
 ************************************************************************/

#pragma once

#include "position.h"
#include "uiDraw.h"
#include <cmath>

/***********************************************************************
 * Class: Geostationary Satellite
 *
 * This is mostly for proof of concept purposes.
 * We were asked to mimic the behavior described in the W07 Lab where
 * the satellite followed a geostationary pattern.
 * This is, of course, easy to replicate as we just position the satellite
 * at a fixed distance away from the earth. (the center point on the screen)
 ************************************************************************/
class GeostationarySatellite {
public:
   GeostationarySatellite(Position tr) {
      do {
         p.setPixels( // anywhere on the screen
            tr.getPixelsX() * random(-0.5, 0.5),
            tr.getPixelsY() * random(-0.5, 0.5)
         );
      } // any consistent position on screen except for on top of earth
      while(
         computeDistance(p, Position()) < EARTH_RADIUS ||
         computeDistance(p, Position()) > computeDistance(Position(tr.getMetersX(), 0.0), Position())
      );
      
      // keep this consistent for geostationary orbital pattern
      distFromEarth = p.getMagnitude();
      
      // angle
      double a0 = 0.0;           // initial angle (rad)
      angle = a0;                // initialize angle
      da = random(-0.02, 0.02);  // change in angle (rad/frame) (constant val)
   }
    
   void update(const Interface * pUI) {
      angle += da;
   }
   
   void handleInput(const Interface * pUI) { }
   
   void display() const {
      drawHubble(p, angle);
   }
   
   /********************************************
    * public methods which will help Simulator
    * class mock geostationary orbit motion
    ********************************************/
   
   // method that directly asks for earthAngle as a parameter, this will simplify
   // how Simulator sets the new GS position relative to the earth (center point)
   void setRelativePosition(double earthAngle) {
      p.setMetersPolar(distFromEarth, earthAngle);
   }
   
   // manual getters/setters
   void setPosition(Position p)  { this->p = p; }
   Position getP() const         { return p;}
    
private:
   Position p;
   double angle;
   double da;
   double distFromEarth;
    
};
