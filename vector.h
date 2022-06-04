/*************************************************************
 * Header File: Vector
 *****************************************************************/

#pragma once

#include <iostream>
#include <cassert>
#include <cmath> // for sin/cos (at least for now until we get Trig class implemented)

/*********************************************
 * CLASS Vector
 * Base class for all classes with a need for
 * an x and y component.
 *********************************************/
class Vector {
public:
   // constructors
   Vector() : Vector(0.0, 0.0) {            } // default constructor
   Vector(double x, double y)  { set(x, y); } // normal "
   Vector(const Vector& s)     { *this = s; } // copy "
   Vector & operator = (const Vector & rhs) { // assignment operator '='
      set(rhs.getX(), rhs.getY()); return *this;
   }

   // getters
   double getX() const { return x; }
   double getY() const { return y; }

   // setters
   void setX(double x) { this->x = x; }
   void setY(double y) { this->y = y; }

   void set(double x, double y) {
      setX(x);
      setY(y);
   }
   
   void set(Vector & s) { set(s.getX(), s.getY()); }
   
   void setPolar(double magnitude, double angleRadians) {
      set(magnitude * sin(angleRadians), magnitude * cos(angleRadians));
   }
   
   // adders
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
   
   // helper methods
   double getMagnitude() const { return sqrt((x*x) + (y*y)); }
   void addMagnitude(double magnitude, double angleRadians) {
      add(magnitude * sin(angleRadians), magnitude * cos(angleRadians));
   }
   
   // operators
   Vector& operator+ (const Vector & rhs) {
      // add another vector
      add(rhs.getX(), rhs.getY());
      return *this;
   }

protected:
   double x; // horizontal position (meters)
   double y; // vertical position
};
