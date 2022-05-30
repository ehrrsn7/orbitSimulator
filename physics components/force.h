//
//  force.h
//  orbitSimulator
//
//  Created by Elijah Harrison on 5/29/22.
//

#pragma once

#include "vector.h"
#include "acceleration.h"

/*********************************************
 * CLASS Force
 * Acceleration integrated by mass.
 *********************************************/
class Force : public Vector {
// getX()       | substitutes get ddxdm/dt
// getY()       | substitutes get ddydm/dt
// magnitude()  | substitutes get force
   
public:
   // constructors
   Force() : Vector(0.0, 0.0)  {              } // default constructor
   Force(double fx, double fy) { set(fx, fy); } // normal "
   Force(const Force& s)       { *this = s;   } // copy "
   Force & operator = (const Force & rhs) { // assignment operator '='
     set(rhs.getX(), rhs.getY()); return *this;
  }
 
   // getters
   Acceleration toAcceleration(double mass) const {
      return Acceleration(getX()/mass, getY()/mass);
   }
    
};
