//
//  acceleration.h
//  orbitSimulator
//
//  Created by Elijah Harrison on 5/29/22.
//

#pragma once

#include "vector.h"


/*********************************************
 * CLASS Acceleration
 * A change in Velocity.
 *********************************************/
class Acceleration : public Vector {
// getX()       | substitutes get ddx
// getY()       | substitutes get ddy
// magnitude()  | substitutes get acceleration
    
public:
   // constructors
   Acceleration() : Vector(0.0, 0.0)    {                } // default constructor
   Acceleration(double ddx, double ddy) { set(ddx, ddy); } // normal "
   Acceleration(const Acceleration& s)  { *this = s;     } // copy "
   Acceleration & operator = (const Acceleration & rhs) { // assignment operator '='
      set(rhs.getX(), rhs.getY()); return *this;
   }
};
