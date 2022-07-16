/**********************************************************************
 * MovingObject.h
 * orbitSimulator
 **********************************************************************/

#pragma once

#include "physicsFormulas.h"
#include "uiInteract.h"
#include "uiDraw.h"
//#define GRAV_CONST 9.8

/**************************************************
 * CLASS Moving Object
 *    Parent of all of the objects that have
 *    mass, position and velocity.
 **************************************************/
class MovingObject {
    
public:
   // constructors
   MovingObject() : alive(true), r(1.0), m(1.0), angle(0.0), dAngle(10.0) { }
   
   virtual void update(const Interface * pUI) {
      double dt = dilateTime(pUI->getDeltaTime());
      v += a * dt;
      p += v * dt;
      rotate(dt);
   }
   
   virtual void display() const {
      if (showHitboxes) drawCircle(p, r); // draw hitbox
   }

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
   static void setShowHitboxes(bool show)       { showHitboxes = show; }
   static void toggleShowHitboxes()             { showHitboxes = !showHitboxes; }
   
   // getters
   Position getPosition()           const { return p; }
   Velocity getVelocity()           const { return v; }
   Acceleration getAcceleration()   const { return a; }
   bool isAlive()                   const { return alive; }
   double getRadius()               const { return r; }
   double getMass()                 const { return m; }
   double getAngle()                const { return angle; }
   double getDAngle()               const { return dAngle; }
   static bool getShowHitboxes()          { return showHitboxes; }
   
   // adders
   void addAngle(double dAngle) { setAngle(getAngle() + dAngle); }
   void addPosition(Position dPosition) { setPosition(getPosition() + dPosition); }
   void addVelocity(Velocity dVelocity) { setVelocity(getVelocity() + dVelocity); }
   
   // other
   void hit() { setAlive(false); }
   
   /**************************************************
    * public helper methods
    **************************************************/
   void applyGravity(const MovingObject & obj, double dt) {
      // obj: object with mass that is attracting this (the earth)
      a = forceDueToGravity(obj, *this) / getMass();
   }

protected:
   Position p;
   Velocity v;
   Acceleration a;
   bool alive;       // display/hide and/or remove from its list
   double r;         // radius
   double m;         // mass (kg)
   double angle;     // current angle to be drawn at
   double dAngle;    // dingle dangle, change my angle
   
   static bool showHitboxes;
   
   /**************************************************
    * private helper methods
    **************************************************/
   virtual void rotate(double dt) { addAngle(dAngle * dt); }
};
