/*************************************************************************
 * Header File: Physics Components
 *
 * All the physics components which are classified as vectors should go
 * here, with the exception of the Position class which is a bit more
 * sophisticated and crucial to the program (for example, to the code in
 * uiDraw, uiInteract and main).
 *************************************************************************/

#pragma once

//#define G 6.67384e-11

#include "vector.h"
#include "position.h"


/**************************************************
 * CLASS Velocity
 * A change in Position.
 **************************************************/
class Velocity : public Vector {

// to not overcomplicate things, let's rely on Vector's get/set components
// for our getters/setters in the child classes:

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
   
   // operators
   Position operator*(const double& rhs); // v{this} * Δt{rhs} -> Δp{Posiiton}
   Position operator*(const double rhs); // when reference is unavailable
};

/**************************************************
 * CLASS Acceleration
 * A change in Velocity.
 **************************************************/
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
   
   // operators
   Velocity operator*(const double& rhs); // v{this} * Δt{rhs} -> Δp{Posiiton}
   Velocity operator*(const double rhs); // when reference is unavailable
};

/**************************************************
 * CLASS Force
 * Acceleration integrated by mass.
 **************************************************/
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
      // (note: make sure Acceleration class is defined before this line of code)
      return Acceleration(getX()/mass, getY()/mass);
   }
    
};

/**************************************************
 * CLASS Gravity
 * A special kind of force which describes
 * force due to gravity.
 **************************************************/
class Gravity : public Force {
// getX()       | substitutes get ddxdm/dt
// getY()       | substitutes get ddydm/dt
// magnitude()  | substitutes get force due to gravity
   
private:
//   static double g; // acceleration due to gravity (value set in gravity.cpp, defined here in header)
   // should this ^^^ be a constant? or should it be variable like in the Howitzer lab?
   // I feel like g should be calculated via the g = G * (m1 m2)/d^2 formula between all objects on the screen to each other

public:
   // constructors
   Gravity() : Force(0.0, 0.0)   {              } // default constructor
   Gravity(double fx, double fy) { set(fx, fy); } // normal "
   Gravity(const Gravity& s)     { *this = s;   } // copy "
   Gravity & operator = (const Gravity & rhs) { // assignment operator '='
      set(rhs.getX(), rhs.getY()); return *this;
   }
};
