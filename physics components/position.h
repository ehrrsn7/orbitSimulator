/*************************************************************************
 * Header File:
 *    Point : The representation of a position 
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen
 *    or the location on the field.
 *
 * Note: Adapted to inherit Vector.
 *    x and y were moved to Vector class and getMeters x and y were
 *    changed to get x and y, and getMeters x and y here were mapped
 *    to call those methods in the Vector parent class.
 *    Previously, all this functionality was involved in one single class.
 *    --elijah
 *************************************************************************/


#pragma once

#include "vector.h"

class TestPosition;

/**************************************************
 * CLASS Position
 * A single position on the field in Meters.
 * Position is responsible for keeping track of
 * both the meters representation of the
 * Simulator and the pixels drawn to the screen
 * via the ogstream object.
 **************************************************/
class Position : public Vector {
public:
   friend class TestPosition;
   
   // constructors
   Position() : Position(0.0, 0.0) { }          // non-default constructor
   Position(double metersX, double metersY) : Vector(metersX, metersY) { }
   Position(const Vector & pt) { *this = pt; }  // copy constructor
   Position & operator = (const Position & pt); // assignment operator '='
   
   // getters
   double getMetersX() const { return getX(); } // from Vector parent class
   double getMetersY() const { return getY(); }
   
   double getPixelsX() const { return getMetersX() / metersFromPixels; }
   double getPixelsY() const { return getMetersY() / metersFromPixels; }
   
   // setters
   void setMetersX(double xMeters)  { setX(xMeters); } // from Vector
   void setMetersY(double yMeters)  { setY(yMeters); }
   
   void setMeters(double xMeters, double yMeters) {
      setMetersX(xMeters);
      setMetersY(yMeters);
   }
   
   void setMetersPolar(double magnitudeMeters, double angleRadians) {
      setPolar(magnitudeMeters, angleRadians);
   }
   
   void setPixelsX(double xPixels)  { setMetersX(xPixels * metersFromPixels); }
   void setPixelsY(double yPixels)  { setMetersY(yPixels * metersFromPixels); }
   
   void setPixels(double xPixels, double yPixels) {
      setPixelsX(xPixels);
      setPixelsY(yPixels);
   }
   
   // adders
   void addPixelsX(double dxPixels) { setPixelsX(getPixelsX() + dxPixels);  }
   void addPixelsY(double dyPixels) { setPixelsY(getPixelsY() + dyPixels);  }
   
   void addPixels(double dxPixels, double dyPixels) {
      addPixelsX(dxPixels);
      addPixelsY(dyPixels);
   }
   
   void addMetersX(double dxMeters) { setMetersX(getMetersX() + dxMeters); }
   void addMetersY(double dyMeters) { setMetersY(getMetersY() + dyMeters); }
   
   void addMeters(double dxMeters, double dyMeters) {
      addMetersX(dxMeters);
      addMetersY(dyMeters);
   }
   
   // deal with the ratio of meters to pixels
   double getZoom() const { return metersFromPixels; }
   
   void setZoom(double metersFromPixels) {
      this->metersFromPixels = metersFromPixels;
   }
   
   // operators
   Position& operator+ (const Position & rhs);
   
private:
   static double metersFromPixels;
};

/**************************************************
 * COMPUTE DISTANCE
 * Find the distance between two positions
 **************************************************/
inline double computeDistance(const Position& pos1, const Position& pos2) {
   return sqrt((pos1.getMetersX() - pos2.getMetersX()) * (pos1.getMetersX() - pos2.getMetersX()) +
               (pos1.getMetersY() - pos2.getMetersY()) * (pos1.getMetersY() - pos2.getMetersY()));
}

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Position& rhs);
std::istream & operator >> (std::istream & in,        Position& rhs);


/**************************************************
 * PT
 * Trivial point
 **************************************************/
struct PT {
   double x;
   double y;
};

