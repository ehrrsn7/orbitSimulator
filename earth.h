/***********************************************************************
 * earth.h
 ************************************************************************/

#pragma once

#include "position.h"
#include "uiInteract.h"
#include "uiDraw.h"

#define EARTH_APPROX_RADIUS 6371000.0

/***********************************************************************
 * Class: Earth
 *
 * This is an overly simple class.
 * It only really contains some information about the Earth drawn on
 * the screen, and display() calls drawEarth() from uiDraw.
 ************************************************************************/
class Earth {
public:
   Earth() : angle(0.0) { }

   void update(const Interface * pUI) { addAngle(0.01); }
   void display() const { drawEarth(p, angle); }
   void handleInput(const Interface * pUI) { }
   
   // getters/setters
   double getAngle() const       { return angle; }
   void setAngle(double angle)   { this->angle = angle; }
   void addAngle(double da)      { setAngle(getAngle() + da); }
   
private:
   Position p; // always 0,0 but we keep it for clarity/efficiency
   double angle;
};

