/**********************************************************************
 * Source File: Physics Formulas
 *
 * (We have a collection of procedural functions here because each math
 * helper function does not retain state)
 **********************************************************************/
 
#define FPS 30 // frames/s
#define SECONDS_IN_DAY 86400 // s
 
#include "earth.h"               // for EARTH_RADIUS
#include "physicsComponents.h"   // for ACCEL_DUE_TO_GRAVITY_EARTH
#include "position.h"            // for Position
 
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
 
/**************************************************
 * Earth Functions
 **************************************************/
 
/**************************************************
 * rotation speed
 * speed = -(2π/frame rate) * (dialation / seconds in day)
 *    rf - rotation of the earth in radians per 1 frame
 *    frame rate - "
 *    timeDilation - "
 *    seconds in day - number of seconds for 1 earth rotation
 **************************************************/
double rotationSpeed() {
   // n is the current time of the software from callback
   return -(2 * M_PI / FPS) * (timeDilation() / SECONDS_IN_DAY);
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
 
double calcHeight(const Position & p, const Earth & e) {
   // should the earth not strictly be at the origin
   return sqrt(
      pow(p.getMetersX() - e.getPosition().getMetersX(), 2) +
      pow(p.getMetersY() - e.getPosition().getMetersY(), 2)
   ) - EARTH_RADIUS;
}
 
/**************************************************
 * direction of gravity pull
 * a = atan2(xe - xs, ye - ys)
 *    e - earth, s - object/satellite
 *    *note that x and y are backwards, this is on purpose...:L
 **************************************************/
double directionOfGravity(const MovingObject & obj1, const MovingObject & obj2) {
   return atan2(
      obj1.getPosition().getMetersX() - obj2.getPosition().getMetersX(),
      obj1.getPosition().getMetersY() - obj2.getPosition().getMetersY()
   );
}
 
 
 
double getGravityOf(const MovingObject& obj1, const MovingObject& obj2) {
   return 0.0;
}
 
 
/**********************************************************************
 * Motion
 **********************************************************************/
 
/**************************************************
 * motion with constant acceleration
 **************************************************/
double aToD(const Acceleration& a, const Velocity& v0, double dt, double initialD) {
   return initialD + v0.mag() * dt + a.mag() * pow(dt, 2);
   // dEjA vUUUUoo 🥹🚗
}
 
/**************************************************
 * x component of motion with constant acceleration
 **************************************************/
double aToX(const Acceleration& a, const Velocity& v0, double dt, double initialD) {
   return initialD + v0.getX() * dt + a.getX() * pow(dt, 2);
   // return toX(aToD(a, v0, dt, initialD), Velocity(a * dt + v0).getAngleRadians());
}
 
/**************************************************
 * y component of motion with constant acceleration
 **************************************************/
double aToY(const Acceleration& a, const Velocity& v0, double dt, double initialD) {
   return initialD + v0.getY() * dt + a.getY() * pow(dt, 2);
   // return toX(aToD(a, v0, dt, initialD), Velocity(a * dt + v0).getAngleRadians());
}
 
/**************************************************
 * velocity with constant acceleration
 **************************************************/
Velocity aToV(const Acceleration& a, const Velocity& v0, const double dt) {
//   return v0 + a * dt; // TODO: uncomment and fix
   return Velocity();
}
 
/**************************************************
 * x component of velocity with constant acceleration
 **************************************************/
double aToDx(const Acceleration& a, const Velocity& v0, double dt) {
   return v0.getX() + a.getX() * dt;
   // return toX(aToV(a, v0, dt));
}
 
/**************************************************
 * y component of velocity with constant acceleration
 **************************************************/
double aToDy(const Acceleration& a, const Velocity& v0, double dt) {
   return v0.getY() + a.getY() * dt;
   // return toY(aToV(a, v0, dt));
}
