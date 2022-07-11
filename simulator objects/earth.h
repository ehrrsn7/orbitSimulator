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
#define G                           6.67384e-11 // N kg⁻² m² (gravitational constant)

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
      setMass(EARTH_MASS); // kg
      setAngle(0.0); // rad
      setDAngle(0.3); // rad/s
   }
   
   void update(const Interface * pUI) override {
      double dt =  dilateTime(pUI->getDeltaTime());
      v += a * dt;
      p += v * dt;
      rotate(dt);
   }
   
   void display() const override { drawEarth(p, angle); }
   
   void rotate(double dt) override 
   {
      addAngle(earthRotationSpeed(dt));
   }
};

