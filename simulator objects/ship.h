/**********************************************************************
 * ship.h
 * orbitSimulator
 **********************************************************************/


#pragma once

#include "movingObject.h"
#include "satellite.h"
#include "uiInteract.h"
#include "uiDraw.h"

#define FIRE_PROJECTILE_COOLDOWN .1 // s

/**************************************************
 * Projectile
 * To be returned by Ship via the fire() method return value.
 * Objects will then be stored in Simulator::projectiles[]
 **************************************************/
class Projectile : public MovingObject {
public:
   Projectile() : expirationTime(2 /* s */ ) {
      setRadius(Position().pixelsToMeters(.5)); // *diameter of 1px*
      setMass(1); // kg
   }

   void update(const Interface * pUI) {
      MovingObject::update(pUI);
      if (expirationTime > 0) expirationTime -= pUI->getDeltaTime();
      else setAlive(false);
   }
   
   void display() const { drawProjectile(p); }
   
private:
   double expirationTime;
};

/**************************************************
 * Dream Chaser (Space Ship)
 
 * The Sierra Nevada Corporation has developed a reusable spaceplane called the Dream Chaser.
 * In our simulation, this spaceplane will be controlled by the user.
 * Initially, the spaceplane is in the upper left corner of the screen (-450px, 450px) moving down slowly (0.0 m/s, -2,000 m/s). It can be drawn with drawShip() and has a radius of 10 pixels.

 * Each time the user presses the right keyboard arrow, the Dream Chaser will rotate to the right 0.1 radians and every time the user presses on the left keyboard arrow, it will rotate to the left by 0.1 radians.
 * Pressing the down-arrow will accelerate the spaceplane by 30.0 m/s2.
 * Acceleration will be along the direction the Dream Chaser is pointed, not the direction of travel.
 * To determine how much the acceleration will affect the velocity of the ship, it is necessary to take into account the direction the ship is pointed and how many seconds the thrust counts in the simulation.
 * For example, if the simulation has 3600 seconds of simulation time to 1 second of player time, and if the simulation is running at 30 frames/second, then one depression of the button will accelerate the ship for 120 seconds (or 2 minutes).
 * Thus vt = v0 + a t so the change in speed will be 600 m/s.
 
 * Each time the user presses the space bar, the Dream Chaser will launch a projectile.
 * This is how space fragments will be removed from the simulation.
 * A projectile adds 9,000 m/s to the ship's velocity and is fired in the direction the ship is pointed.
 * It is also necessary to start the projectile's path at 19 pixels in front of the ship.
 * This can be accomplished with ptShipFront = rotate(ptShipCenter, 0.0, 19.0, radians).
 * A projectile is 1 pixel in diameter and travels for 70 game units or about 2 seconds.
 * When the time has expired, it disappears much like a fragment.
 
 * Amount: 1
 **************************************************/
class SpaceShip : public Satellite {
public:
   SpaceShip() : drawThrust(false), cooldownTimer(0) {
      p.setPixels(-450.0, 450.0); // px
      v.set(0.0, -2000.0); // m/s
      setRadius(Position().pixelsToMeters(10)); // px
   }
   
   void update(const Interface * pUI) override {
      MovingObject::update(pUI);
      cooldownTimer -= pUI->getDeltaTime();
   }
   
   // const Position& center, double rotation, bool thrust
   void display() const override {
      MovingObject::display();
      drawShip(p, angle, drawThrust);
   }
   
   void handleInput(const Interface * pUI) override {
      // handle acceleration (down arroy key)
      
      // down arrow will accelerate ship in direction it's facing at 30m/s/s
      if (pUI->isDown()) a.addPolar(30.0 /*m/s/s*/, getAngle());
      
      // draw flames when ship is 'accelerating'
      if (pUI->isDown()) drawThrust = true;
      else drawThrust = false;
      
      // handle angle (l/r arrow keys)
      setDAngle(0); // reset each frame, then set:
      // user right arrow -> rotate +0.1 radians
      if (pUI->isLeft()) dAngle -= 0.1 * pUI->getDeltaTime();
      // user left arrow -> rotate -0.1 radians
      if (pUI->isRight()) dAngle += 0.1 * pUI->getDeltaTime();
       
      // fire projectiles: handle in simulator -- see fire() method below
   }
   
   Projectile fire() {
      // handle cooldown timer
      assert(timeToFireProjectile()); // never fire projectile if cooldownTimer has not finished
      setCooldownTimer(FIRE_PROJECTILE_COOLDOWN);
      
      Projectile projectile;
      projectile.setAngle(getAngle());

      // set to ship position + offset
      Position posOffset;
      posOffset.addPolar(pixelsToMeters(19), getAngle());
      projectile.setPosition(this->getPosition() + posOffset);

      // set to ship velocity + projectile speed
      Velocity velOffset;
      velOffset.addPolar(9000 /* m/s */, getAngle());
      projectile.setVelocity(velOffset + this->getVelocity());
      
      return projectile;
   }
   
   void setCooldownTimer(double cooldownTime) { this->cooldownTimer = cooldownTime; }
   double getCooldownTimer() const { return cooldownTimer; }
   bool timeToFireProjectile() const { return cooldownTimer <= 0; }
   
private:
   double cooldownTimer;
   bool drawThrust;
};
