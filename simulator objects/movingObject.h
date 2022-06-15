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
   MovingObject() { }
   
   virtual void update() {}
   virtual void display() {}
   virtual void handleInput(const Interface * pUI) { }
   
   // setters
   void setPosition(const Position & p) { this->p = p; }
   
   // getters
   Position getPosition() const { return p; }
    
   // mass
   void setMass(double mass) { m = mass; }
   double getMass() const { return m; }

private:
   double m; // mass (kg)
   Position p;
   Velocity v;
   Acceleration a;
};

/**************************************************
 * Other MovingObject Classes
 **************************************************/
class Hubble : MovingObject {};
class SpaceShip : MovingObject {};
class CrewDragon : MovingObject {};
class Sputnik : MovingObject {};
class GPS : MovingObject {};
class Starlink : MovingObject {};
