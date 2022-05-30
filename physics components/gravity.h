//
//  gravity.h
//  orbitSimulator
//
//  Created by Elijah Harrison on 5/29/22.
//

#pragma once

#define ACCEL_DUE_TO_GRAVITY 9.8 // m/s/s

#include "force.h"

class MovingObject;

/*********************************************
 * CLASS Gravity
 * A special kind of force which describes
 * force due to gravity.
 *********************************************/
class Gravity : public Force {
// getX()       | substitutes get ddxdm/dt
// getY()       | substitutes get ddydm/dt
// magnitude()  | substitutes get force due to gravity
   
private:
   static double g; // acceleration due to gravity (value set in gravity.cpp, defined here in header)

public:
   // constructors
   Gravity() : Force(0.0, 0.0)   {              } // default constructor
   Gravity(double fx, double fy) { set(fx, fy); } // normal "
   Gravity(const Gravity& s)     { *this = s;   } // copy "
   Gravity & operator = (const Gravity & rhs) { // assignment operator '='
      set(rhs.getX(), rhs.getY()); return *this;
   }
};
