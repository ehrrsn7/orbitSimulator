//
//  velocity.h
//  Lab07
//
//  Created by Elijah Harrison on 5/29/22.
//

#pragma once

#include "vector.h"

/*********************************************
 * CLASS Velocity
 * A change in Position.
 *********************************************/
class Velocity : public Vector {

// to not overcomplicate things, let's rely on Vector's get/set components for our getters/setters in the child classes:

// getX()       | substitutes get dx
// getY()       | substitutes get dy
// magnitude()  | substitutes get speed
    
public:
   // constructors
   Velocity() : Vector(0.0, 0.0)  {              } // default constructor
   Velocity(double dx, double dy) { set(dx, dy); } // normal "
   Velocity(const Velocity& s)    { *this = s;   } // copy "
   Velocity & operator = (const Velocity & rhs) {  // assignment operator '='
      set(rhs.getX(), rhs.getY()); return *this;
   }
};
