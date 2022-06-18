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
