/***********************************************************************
 * Source File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#include "vector.h"

void Position::setMeters(double xMeters, double yMeters) {
   setMetersX(xMeters);
   setMetersY(yMeters);
}

void Position::setMetersPolar(double magnitudeMeters, double angleRadians) {
   setPolar(magnitudeMeters, angleRadians);
}

void Position::setPixels(double xPixels, double yPixels) {
   setPixelsX(xPixels);
   setPixelsY(yPixels);
}

/**************************************************
 * method: add
 * class: Position
 * Assign a Point
 * Note: basically the definition of Vector+=
 **************************************************/
void Position::add(const Velocity& dv, double dt) {
   add(Velocity(dv.getX() * dt, dv.getY() * dt));
}

void Position::addPixels(double dxPixels, double dyPixels) {
   addPixelsX(dxPixels);
   addPixelsY(dyPixels);
}

void Position::addMeters(double dxMeters, double dyMeters) {
   addMetersX(dxMeters);
   addMetersY(dyMeters);
}

void Position::setZoom(double metersFromPixels) {
   this->metersFromPixels = metersFromPixels;
}

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
 * Adds another point to this* and returns it as a new Position
 **************************************************/
Position Position::operator+ (const Position & rhs) {
   Position newP;
   newP.add(rhs);
   return newP;
}

/**************************************************
 * operator +=
 * class: Position
 * Adds another point to this*
 **************************************************/
Position& Position::operator+= (const Position & rhs) {
   // add another vector
   this->add(rhs);
   return *this;
}

/**************************************************
 * operator - (subtraction)
 * class: Position
 * Subtracts another point from this*
 **************************************************/
Position Position::operator- (const Position & rhs) {
   Vector::add(-rhs.getX(), -rhs.getY());
   return *this;
}

/**************************************************
 * operator - (negative)
 * class: Position
 * Converts *this into its negative counterpart
 **************************************************/
Position Position::operator- () {
   Vector::set(-this->getX(), -this->getY());
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

/**************************************************
 * STATICS
 **************************************************/
//
///**************************************************
// * CLASS Position
// * METHOD
// * METERS TO PIXELS
// *
// * takes parameter meters and converts it to pixels
// * according to conversion constant (static double
// * defined in Position class)
// *
// * param - meters : double
// * return - double
// **************************************************/
//double Position::metersToPixels(double meters) {
//   return meters / Position::metersFromPixels;
//}
//
///**************************************************
//* CLASS Position
//* METHOD
//* PIXELS TO METERS
//*
//* takes parameter meters and converts it to meters
//* according to conversion constant (static double
//* defined in Position class)
//*
//* param - pixels : double
//* return - double
//**************************************************/
//double Position::pixelsToMeters(double pixels) {
//   return pixels * Position::metersFromPixels;
//}
//
