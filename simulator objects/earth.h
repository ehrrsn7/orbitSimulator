/**********************************************************************
 * earth.h
 * orbitSimulator 
 **********************************************************************/

#pragma once

#include "movingObject.h" // for MovingObject
#include "uiDraw.h" // for drawEarth

#define EARTH_RADIUS                6371000.0   // m
#define EARTH_MASS                  5.972e24    // kg
#define ACCEL_DUE_TO_GRAVITY_EARTH  9.80665     // m/s/s

/**************************************************
 * CLASS Earth
 *    This is an overly simple class.
 *    It only really contains some information about
 *    the Earth drawn on the screen, and display()
 *    calls drawEarth() from uiDraw.
 **************************************************/
class Earth : public MovingObject {
public:
   Earth() {
      setRadius(EARTH_RADIUS); // px
      setAngle(0.0); // rad
      setDAngle(0.3); // rad
      setMass(EARTH_MASS); // kg
   }
   
   void display() const { drawEarth(p, angle); }
};

