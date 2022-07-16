/**********************************************************************
 * geostationarySatellite.h
 * orbitSimulator
 **********************************************************************/

#pragma once

#include "movingObject.h" // MovingObject, vector.h, ui*.h

/**************************************************
 * CLASS Geostationary Satellite
 *    This is mostly for proof of concept purposes.
 *    We were asked to mimic the behavior described
 *    in the W07 Lab where the satellite followed a
 *    geostationary pattern.
 *    This is, of course, easy to replicate as we
 *    just position the satellite at a fixed
 *    distance away from the earth. (the center
 *    point on the screen)
 **************************************************/
class GeostationarySatellite {
public:
   GeostationarySatellite(Position tr) : angle(0.0), da(random(-0.02, 0.02)) {
      do {
         p.setPixels( // anywhere on the screen
            tr.getPixelsX() * random(-0.5, 0.5),
            tr.getPixelsY() * random(-0.5, 0.5)
         );
      } // any cosistent position on screen except for on top of earth
      while(computeDistance(p, Position()) < EARTH_RADIUS ||
            computeDistance(p, Position()) > min(tr.getMetersX(), tr.getMetersY())
      );
      
      // keep this consistent for geostationary orbital pattern
      distFromEarth = p.getMagnitude();
   }
    
   void update(const Interface * pUI) {
      angle += da;
   }
   
   void display() const {
      drawHubble(p, angle);
   }
   
   void handleInput(const Interface * pUI) { }
   
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
