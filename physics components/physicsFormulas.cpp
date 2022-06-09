/***********************************************************************
 * Source File: Physics Formulas
 *
 * (We have a collection of procedural functions here because each math
 * helper function does not retain state)
 ***********************************************************************/

#include "earth.h"               // for EARTH_RADIUS
#include "physicsComponents.h"   // for ACCEL_DUE_TO_GRAVITY_EARTH
#include "position.h"            // for Position

#include <cmath>                 // for math functions

/************************************************************************
 * Time Functions
 ************************************************************************/
// dialation = hours in Day * minutes in hour
double dialateTime() {return 24 * 60;}

// frame time = dialation / frame rate
double timePerFrame() {return dialateTime() / 30;}

/************************************************************************
 * Earh Functions
 ************************************************************************/
// speed = -(2 n/frame time) * (dialation / seconds in day)
double rotateSpeed(double n)
{
   //n is the current time of the software from callback
   return -(2 * n / timePerFrame()) * (dialateTime() / 86400);
}

//
double calcGravity(double height)
{
   auto firstCalc = (EARTH_RADIUS * (EARTH_RADIUS + height)) * (EARTH_RADIUS * (EARTH_RADIUS + height));
   auto secondCalc = ACCEL_DUE_TO_GRAVITY_EARTH * firstCalc;
   return secondCalc;
}

//
double calcHeight(const Position & p)
{
   auto x_2 = p.getMetersX() * p.getMetersX();
   auto y_2 = p.getMetersY() * p.getMetersY();
   return sqrt(x_2 + y_2) - EARTH_RADIUS;
}

//
double directionOfGravity(const Position & satiliteP)
{
   return atan2(0 - satiliteP.getMetersX(), 0 - satiliteP.getMetersY());
}

// horizontal component of acceleration from acceleration magnitude
double horizAccel(double a, double angleRadians)
{
   return a * sin(angleRadians);
}

// vertical component of acceleration from acceleration magnitude
double vertAccel(double a, double angleRadians)
{
   return a * cos(angleRadians);
}

/************************************************************************
 * Motion
 ************************************************************************/
// horizontal and vertical distance from constant acceleration
double distanceFormulaHoriz(double intialD, const Velocity & v0,
                            double time, const Acceleration & a)
{
   return intialD + (v0.getX() * time) + (0.5 * (a.getX() * (time * time)));
   
   // dEjA vUUUUoo
}

double distanceFormulaVert(double intialD, const Velocity & v0,
                           double t, const Acceleration & a)
{
   return intialD + (v0.getY() * t) + (0.5 * (a.getY() * (t * t)));
}

// horizontal and vertical velocity from constant acceleration
double velocityConstantAccelHoriz(const Velocity & v0, const Acceleration & a, double t)
{
   return v0.getX() + (a.getX() * t);
}

double velocityConstantAccelVert(const Velocity & v0, const Acceleration & a, double t)
{
   return v0.getY() + (a.getY() * t);
}

double x(Vector& v) { return sin(v.getMagnitude()); }
double y(Vector& v) { return cos(v.getMagnitude()); }

Velocity constantAccelerationToVelocity(const Acceleration& constantAcceleration, const Velocity& initialVelocity, double changeInTime) {
   Velocity newVelocity(initialVelocity);
   newVelocity.add(constantAcceleration.getX() * changeInTime, constantAcceleration.getY() * changeInTime);
   return newVelocity;
}

/*
Velocity aToVn(const Acceleration& a, const Velocity& v0, double dt) {
   return Velocity(v0 + a*t);
}
 
v.set(x(aToVn(9.8, this->v, dt)));
*/
