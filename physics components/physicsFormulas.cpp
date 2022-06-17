/**********************************************************************
 * Source File: Physics Formulas
 *
 * (We have a collection of procedural functions here because each math
 * helper function does not retain state)
 **********************************************************************/
 
#define FPS 30                   // frames/s
#define SECONDS_IN_DAY 86400     // s : 60s/min * 60min/hr * 24hr/d
 
#include "physicsFormulas.h"     // header file
 
#include <cmath>                 // for math functions
 

/**********************************************************************
 * Horizontal/Vertical Components
 *    Note: 'Vector&' is polymorphic -- it refers to either itself or
 *    any child of Vector.
 **********************************************************************/
double trigX(const double mag, const double angleRadians)
   { return mag * sin(angleRadians); }
double trigY(const double mag, const double angleRadians)
   { return mag * cos(angleRadians); }
 
double trigX(const Vector & v) { return trigX(v.mag(), v.angle()); }
double trigY(const Vector & v) { return trigY(v.mag(), v.angle()); }

/**********************************************************************
* Distance Functions
**********************************************************************/

/**************************************************
 * distance(position1, position2)
 * Distance = √[(p1.x-p2.x)^2 + (p1.y-p2.y)^2]
 **************************************************/
double distance(const Position& pos1, const Position& pos2) {
   return sqrt(
      (pos1.getMetersX() - pos2.getMetersX()) * (pos1.getMetersX() - pos2.getMetersX()) +
      (pos1.getMetersY() - pos2.getMetersY()) * (pos1.getMetersY() - pos2.getMetersY())
   );
}

/**************************************************
 * Overloaded function for easy converting
 * distance(objects) -> distance(positions)
 * Distance = √[(p1.x-p2.x)^2 + (p1.y-p2.y)^2]
 **************************************************/
double distance(const MovingObject& obj1, const MovingObject& obj2) {
   return distance(obj1.getPosition(), obj2.getPosition());
}

/**********************************************************************
 * Time Functions
 **********************************************************************/
 
/**************************************************
 * time dilation
 * dialation = hours in Day * minutes in hour
 *    td - ratio of simulator time to real-world time
 *    hours in day - 24
 *    minutes in hour - 60
 **************************************************/
double timeDilation() {return 24 * 60; }
 
/**************************************************
 * time per frame
 * frame time = dialation / frame rate
 *    tpf - real-world time in seconds for each frame in the simulator
 *    frame rate - fps defined in simulator, 30 in our case
 *    timeDilation - "
 **************************************************/
double timePerFrame() {return timeDilation() / FPS; }
 
/**********************************************************************
 * Earth Functions
 **********************************************************************/
 
/**************************************************
 * rotation speed
 * speed = -(2π/frame rate) * (dialation / seconds in day)
 *    rf - rotation of the earth in radians per 1 frame
 *    frame rate - "
 *    timeDilation - "
 *    seconds in day - number of seconds for 1 earth rotation
 **************************************************/
double rotationSpeed() {
   return -(2 * M_PI / FPS) * (timeDilation() / SECONDS_IN_DAY);
}

/**********************************************************************
* Gravity Functions
**********************************************************************/

/**************************************************
 * height above the earth
 * h = √[x² + y²] - r
 *    √[x² + y²] -> distance from origin
 *    r - radius of earth
 **************************************************/
double calcHeight(const Position & p) {
   return sqrt(
      pow(p.getMetersX(), 2) +
      pow(p.getMetersY(), 2)
   ) - EARTH_RADIUS;
}
 
/**************************************************
 * height above the earth
 * h = √[(x2 - x1)² + (y2 - y1)²] - r
 *    √[x2² + y2²] -> distance from p1
 **************************************************/
double calcHeight(const Position & p, const Earth & e) {
   // should the earth not strictly be at the origin
   return sqrt(
      pow(p.getMetersX() - e.getPosition().getMetersX(), 2) +
      pow(p.getMetersY() - e.getPosition().getMetersY(), 2)
   ) - EARTH_RADIUS;
}
 
/**************************************************
 * direction of gravity pull
 * a = atan2(p.x2 - p.x2, p.y1 - p.y2)
 *    *note that x and y are backwards, this is on purpose...:L
 **************************************************/
double directionOfGravity(const Position& p1, const Position& p2) {
   return atan2(
      p1.getMetersX() - p2.getMetersX(),
      p1.getMetersY() - p2.getMetersY()
   );
}

/**************************************************
 * alias for directionOfGravity(Position, Position)
 * direction of gravity pull
 * a = atan2(p.x2 - p.x2, p.y1 - p.y2)
 **************************************************/
double directionOfGravity(const MovingObject & obj1, const MovingObject & obj2) {
   return directionOfGravity(obj1.getPosition(), obj2.getPosition());
}

/**************************************************
 * gravity due to mass equation
 * Fg = G * m1 m2 / d^2 @angle towards obj2
 * placed beneath directionOfGravity so that it sees it
 **************************************************/
Gravity forceDueToGravity(const MovingObject& obj1, const MovingObject& obj2) {
   Gravity g;
   g.setPolar(
      G * obj1.getMass() * obj2.getMass() / distance(obj1, obj2),
      directionOfGravity(obj1, obj2));
   return g;
}

/**************************************************
* gravity equation
* gh = g (r/(r + h))^2
**************************************************/
double calcGravity(double height) {
 return ACCEL_DUE_TO_GRAVITY_EARTH * (
    pow((EARTH_RADIUS / (EARTH_RADIUS + height)), 2)
 );
}

/**************************************************
* gravity equation
* gh = g (r/(r + h))^2
* but returns a Gravity vector object in the
* direction of the origin
**************************************************/
Gravity calcGravityVector(const Position& p) {
  Gravity g;
  g.setPolar(
     calcGravity(calcHeight(p)),
     directionOfGravity(p, Position())
  );
  return g;
}

/**********************************************************************
 * Motion
 **********************************************************************/
 
/**************************************************
 * motion with constant acceleration
 * s = s0 + v0 * dt + 1/2 * a * dt^2
 **************************************************/
double aToD(const Acceleration& a, const Velocity& v0, double dt, double initialD) {
   return initialD + v0.mag() * dt + .5 * a.mag() * pow(dt, 2);
   // dEjA vUUUUoo 🥹🚗
}
 
/**************************************************
 * x component of motion with constant acceleration
 **************************************************/
double aToX(const Acceleration& a, const Velocity& v0, double dt, double initialD) {
   return initialD + v0.getX() * dt + .5 * a.getX() * pow(dt, 2);
   // return toX(aToD(a, v0, dt, initialD), Velocity(a * dt + v0).getAngleRadians());
}
 
/**************************************************
 * y component of motion with constant acceleration
 **************************************************/
double aToY(const Acceleration& a, const Velocity& v0, double dt, double initialD) {
   return initialD + v0.getY() * dt + .5 * a.getY() * pow(dt, 2);
   // return toX(aToD(a, v0, dt, initialD), Velocity(a * dt + v0).getAngleRadians());
}
 
/**************************************************
 * x component of velocity with constant acceleration
 **************************************************/
double aToDx(const Acceleration& a, const Velocity& v0, double dt) {
   return v0.getX() + a.getX() * dt;
}
 
/**************************************************
 * y component of velocity with constant acceleration
 **************************************************/
double aToDy(const Acceleration& a, const Velocity& v0, double dt) {
   return v0.getY() + a.getY() * dt;
   // return toY(aToV(a, v0, dt));
}

/**************************************************
* velocity with constant acceleration
**************************************************/
Velocity aToV(const Acceleration& a, const Velocity& v0, const double dt) {
//   return v0 + a * dt; // TODO: fix and uncomment
  return Velocity(aToDx(a, v0, dt), aToDy(a, v0, dt));
}
