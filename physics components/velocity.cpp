/**********************************************************************
 * velocity.cpp
 * orbitSimulator
 **********************************************************************/

#include "vector.h"

Velocity& Velocity::operator= (const Velocity & rhs) {
   Vector::set(rhs.getX(), rhs.getY()); return *this;
}
