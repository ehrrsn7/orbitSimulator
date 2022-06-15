/**********************************************************************
 * acceleration.cpp
 * orbitSimulator
 **********************************************************************/

#include "physicsComponents.h"


/**************************************************
 * OPERATOR*
 * Class: Acceleration
 * param: rhs, where rhs is dt or Δt : double&
 * return: Δd : double
 *    - where Δd is a change in velocity
 **************************************************/
Velocity Acceleration::operator* (const double& rhs) { // return Δp
   return Velocity(this->getX() * rhs, this->getY() * rhs); // rhs = Δt
}

/**************************************************
 * OPERATOR*
 * Class: Velocity
 * param: rhs : double (pass-by-value when reference unavailable)
 *    - where rhs is Δt or change in time
 * return: Δd : double
 *    - where Δd is a change in distance
 **************************************************/
Velocity Acceleration::operator*(const double rhs) {
    return Velocity(this->getX() * rhs, this->getY() * rhs); // rhs = Δt
}

