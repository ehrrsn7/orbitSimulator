//
//  physicsFormulas.h
//  orbitSimulator
//
//  Created by Elijah Harrison on 6/1/22.
//

#pragma once

//#include "position.h"
#include <cmath>

/***********************************************************************
 * TODO: write functions or create a class with static methods that gives
 *       the program quick access to all the physics formulas described in
 *       the Lab07 description here in this header file...
 *       This will make the physics components classes easier to read when
 *       we implement them.
 ************************************************************************/
//
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
