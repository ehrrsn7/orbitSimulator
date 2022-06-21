/**********************************************************************
 * earth.h
 * orbitSimulator 
 **********************************************************************/

#pragma once

#include "movingObject.h" // MovingObject, vector.h, ui*.h

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
   Earth() : angle(0.0) { }

   void update(const Interface * pUI) { addAngle(0.3 * pUI->getDeltaTime()); }
   void display() const { drawEarth(p, angle); }
   void handleInput(const Interface * pUI) { }
   
   // getters
   Position getPosition() const { return p; }
   double getAngle() const { return angle; }
   
   // setters
   void setPosition(const Position & p) { this->p = p; }
   void setAngle(double angle) { this->angle = angle; }

   // adders
   void addAngle(double da) { setAngle(getAngle() + da); }
   
private:
   Position p; // always 0,0 but we keep it for clarity/efficiency
   double angle;
};

