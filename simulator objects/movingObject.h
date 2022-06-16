/**********************************************************************
 * MovingObject.h
 * orbitSimulator
 **********************************************************************/

#pragma once

#include "physicsComponents.h"
#include "uiInteract.h"
#include "uiDraw.h"


/**************************************************
 * CLASS Moving Object
 *    Parent of all of the objects that have
 *    mass, position and velocity.
 **************************************************/
class MovingObject {
    
public:
   // constructors
   MovingObject() : alive(true) {
      
   }
   
   virtual void update() { }
   virtual void display() const { }
   virtual void handleInput(const Interface * pUI) { }
   
   // setters
   void setPosition(const Position & p)         { this->p = p; }
   void setVelocity(const Velocity & v)         { this->v = v; }
   void setAcceleration(const Acceleration & a) { this->a = a; }
   void setAlive(const bool alive)              { this->alive = alive; }
   void setRadius(const double r)               { this->r = r; }
   void setMass(double mass)                    { this->m = mass; }
   void setAngle(double angle)                  { this->angle = angle; }
   void setDAngle(double dAngle)                { this->dAngle = dAngle; }
   
   // getters
   Position       getPosition()     const { return p; }
   Velocity       getVelocity()     const { return v; }
   Acceleration   getAcceleration() const { return a; }
   bool           isAlive()         const { return alive; }
   double         getRadius()       const { return r; }
   double         getMass()         const { return m; }
   double         getAngle()        const { return angle; }
   double         getDAngle()       const { return dAngle; }
   
   // other
   void hit() { setAlive(false); }

protected:
   Position p;
   Velocity v;
   Acceleration a;
   bool alive; // display/hide and/or remove from its list
   double r; // radius
   double m; // mass (kg)
   double angle; // current angle to be drawn at
   double dAngle; // dingle dangle, change my angle
   
   /**************************************************
    * helper methods
    **************************************************/
   void rotate() {
      
   }
   
   void applyGravity(const MovingObject & obj) {
      const double G = 6.67384e-11;
      const double d = computeDistance(this->getPosition(), obj.getPosition());
      
      // obj: object with mass that is attracting this
      a.setPolar(
         G * this->getMass() * obj.getMass() / pow(d, 2), // magnitude
         atan2(getPosition().getMetersX() - obj.getPosition().getMetersX(), // angle (radians)
               getPosition().getMetersY() - obj.getPosition().getMetersY())
         
         // directionOfGravity(this, obj)
         // TODO: why does directionOfGravity() throw an error here? ^
         // for now we just pasted the code directly in for now
      );
   }
};

/**************************************************
 * Other MovingObject Classes
 **************************************************/
class Ship : public MovingObject {
public:
   void display() const {
      drawShip(p, angle, false);
   }
};

class Satellite : public MovingObject {};
class Projectile : public MovingObject {};
class SatellitePart : public MovingObject {};
class Fragment : public MovingObject {} ;

class Hubble : public Satellite {};
class SpaceShip : public Satellite {};
class CrewDragon : public Satellite {};
class Sputnik : public Satellite {};
class GPS : public Satellite {};
class Starlink : public Satellite {};
