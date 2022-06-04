//
//  physicsFormulas.h
//  orbitSimulator
//
//  Created by Elijah Harrison on 6/1/22.
//

#pragma once

//#include "position.h"
#include <cmath>
#include "position.h"
#include "physicsComponents.h"
#define EARTH_RADIUS 6378000

/***********************************************************************
 * TODO: write functions or create a class with static methods that gives
 *       the program quick access to all the physics formulas described in
 *       the Lab07 description here in this header file...
 *       This will make the physics components classes easier to read when
 *       we implement them.
 ************************************************************************/
//
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
   auto secondCalc = 9.80665 * firstCalc;
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
//
double horizAccel(double totalAccel, double angle)
{
   return totalAccel * sin(angle);
}
//
double vertAccel(double totalAccel, double angle)
{
   return totalAccel * cos(angle);
}
/************************************************************************
 * Motion
 ************************************************************************/
double distanceFormulaHoriz(double intialD, const Velocity & v,
                       double time, const Acceleration & a)
{
   return intialD + (v.getX() * time) + (0.5 * (a.getX() * (time * time)));
}
double distanceFormulaVert(double intialD, const Velocity & v,
                       double time, const Acceleration & a)
{
   return intialD + (v.getY() * time) + (0.5 * (a.getY() * (time * time)));
}
//
double velocityConstantAccelHoriz(const Velocity & inital, const Acceleration & a, double time)
{
   return inital + (a.getX() * time);
}
double velocityConstantAccelVert(const Velocity & inital, const Acceleration & a, double time)
{
   return inital + (a.getY() * time);
}
//// some good classes to make
//class Trig { // purely static class
//   static double cartesianToMag(double x, double y)   { return sqrt((x*x) + (y*y)); } // meters
//   static double cartesianToMag(Position & p)         { return cartesianToMag(p.getX(), p.getY()); }
//
//   static double cartesianToAngleRadians(double x, double y)   { return atan2(x, y); } // radians
//   static double cartesianToAngleRadians(Position & p)         { return cartesianToAngleRadians(p.getX(), p.getY()); }
//
//   static double polarToX(double magnitudeMeters, double angleRadians)  { return magnitudeMeters * sin(angleRadians); }
//   static double polarToY(double magnitudeMeters, double angleRadians)  { return magnitudeMeters * cos(angleRadians); }
//
//   static Position polarToCartesian(double magnitudeMeters, double angleRadians)  {
//      return Position(Trig::polarToX(magnitudeMeters, angleRadians), Trig::polarToY(magnitudeMeters, angleRadians));
//   }
//
//};
//
//// should we keep this or just use functions defined in <math.h>?? cartesianToAngleRadians is essentially atan2(x,y) from the math library
//
//static class physicsFormulas {
//
//};
