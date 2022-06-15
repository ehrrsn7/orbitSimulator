/**********************************************************************
 * Header File: Vector
 **********************************************************************/

#pragma once

#include <iostream>
#include <cassert>
#include <cmath> // for sin/cos (for now until physicsFormulas.h is done)

/**************************************************
 * CLASS Vector
 *    Base class for all classes with a need for
 *    an x and y component.
 **************************************************/
class Vector {
public:
   /**************************************************
    * Constructors
    **************************************************/
   Vector() : Vector(0.0, 0.0) {            } // default constructor
   Vector(double x, double y)  { set(x, y); } // normal "
   Vector(const Vector& s)     { *this = s; } // copy "
   Vector & operator = (const Vector & rhs) { // assignment operator '='
      set(rhs.getX(), rhs.getY()); return *this;
   }

   /**************************************************
    * Getters
    **************************************************/
   double getX() const { return x; }
   double getY() const { return y; }

   /**************************************************
    * Setters
    **************************************************/
   void setX(double x) { this->x = x; }
   void setY(double y) { this->y = y; }
   
   void set(double x, double y) {
      setX(x);
      setY(y);
   }
   
   void set(Vector & s) { set(s.getX(), s.getY()); }
   
   /**************************************************
    * Adders
    **************************************************/
   void addX(double dx) { setX(getX() + dx); }
   void addY(double dy) { setY(getY() + dy); }
   
   void add(double dx, double dy) {
      addX(dx);
      addY(dy);
   }
   
   void add(Vector & v) {
      // v stands for ds/dt where s is the base vector
      add(v.getX(), v.getY());
   }
   
   /**************************************************
    * Other Getters/Setters
    **************************************************/
   // get
   double mag() const { return getMagnitude(); }
   
   double getMagnitude() const {
      return sqrt(pow(getX(), 2) + pow(getY(), 2));
   }
   
   double getAngleRadians() const { return atan2(getX(), getY()); }
   double angle() const { return getAngleRadians(); }

   // set
   void setPolar(double magnitude, double angleRadians) {
      set(magnitude * sin(angleRadians), magnitude * cos(angleRadians));
   }
   
   // add
   void addMagnitude(double magnitude, double angleRadians) {
      add(magnitude * sin(angleRadians), magnitude * cos(angleRadians));
   }
   
   void addPolar(double magnitude, double angleRadians) {
      add(magnitude * sin(angleRadians), magnitude * cos(angleRadians));
   }
   
   /**************************************************
    * Operators
    **************************************************/
   Vector& operator+ (const Vector & rhs) {
      // add another vector
      add(rhs.getX(), rhs.getY());
      return *this;
   }

protected:
   double x; // horizontal position (meters)
   double y; // vertical position (meters)
};

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Vector& rhs);
std::istream & operator >> (std::istream & in,        Vector& rhs);
