/***********************************************************************
 * Source File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#include "physicsComponents.h"

/**************************************************
 * operator =
 * class: Position
 * Assign a Point
 * Note: basically an override of Vector=
 **************************************************/
Position & Position::operator = (const Position & rhs) {
   setMeters(rhs.getMetersX(), rhs.getMetersY());
   return *this;
}

/**************************************************
 * operator +
 * class: Position
 * Adds another point to this*
 * Note: basically an override of Vector+
 **************************************************/
Position& Position::operator+ (const Position & rhs) {
   // add another vector
   addMeters(rhs.getMetersX(), rhs.getMetersY());
   return *this;
}

/**************************************************
 * POSITION insertion
 *       Display coordinates on the screen
 **************************************************/
std::ostream& operator << (std::ostream& out, const Position& rhs) {
   out << "(" << rhs.getMetersX() << "m , " << rhs.getMetersY() << "m)";
   return out;
}
   
/**************************************************
 * POSITION extraction
 *       Prompt for coordinates
 **************************************************/
std::istream& operator >> (std::istream& in, Position& rhs) {
   double x, y;
   in >> x >> y;
   rhs.setMeters(x, y);
   return in;
}
