/**********************************************************************
 * physicsFormulas.h
 * orbitSimulator
 **********************************************************************/

#pragma once

#include "vector.h"     // for ACCEL_DUE_TO_GRAVITY_EARTH and vector child classes

/**************************************************
 * Prototypes
 **************************************************/
class MovingObject;
class Earth;

/**********************************************************************
 * Horizontal/Vertical Components
 **********************************************************************/
double trigX(const double mag, const double angleRadians);
double trigY(const double mag, const double angleRadians);
 
double trigX(const Vector & v);
double trigY(const Vector & v);

double mag(double x, double y);
double mag(const Vector& s);
double deg(double angleRadians);
double rad(double angleDegrees);

/**********************************************************************
* Distance Functions
**********************************************************************/
double distance(const Position& pos1, const Position& pos2);
double distance(const MovingObject& obj1, const MovingObject& obj2);
double computeDistance(const Position& pos1, const Position& pos2);

/**********************************************************************
 * Time Functions
 **********************************************************************/
double timeDilation();
double dilateTime(double dt);
double timePerFrame();
 
/**********************************************************************
 * Earth Functions
 **********************************************************************/
double rotationSpeed();

/**********************************************************************
* Gravity Functions
**********************************************************************/
double calcHeight(const Position & p);
double calcHeight(const Position & p, const Earth & e);
double directionOfGravity(const Position& p1, const Position& p2);
double directionOfGravity(const MovingObject & obj1, const MovingObject & obj2);
Gravity forceDueToGravity(const MovingObject& obj1, const MovingObject& obj2);
double calcGravity(double height);
Gravity calcGravityVector(const Position& p);

/**********************************************************************
 * Motion
 **********************************************************************/
double aToD(const Acceleration& a, const Velocity& v0, double dt, double initialD);
double aToX(const Acceleration& a, const Velocity& v0, double dt, double initialD);
double aToY(const Acceleration& a, const Velocity& v0, double dt, double initialD);
double aToDx(const Acceleration& a, const Velocity& v0, double dt);
double aToDy(const Acceleration& a, const Velocity& v0, double dt);
Velocity aToV(const Acceleration& a, const Velocity& v0, const double dt);
