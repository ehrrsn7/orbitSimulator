//
//  satellites.cpp
//  orbitSimulator
//
//  Created by Elijah Harrison on 6/23/22.
//

#include "satellite.h" // header file
#include "movingObject.h" // for Fragment class

/**************************************************
 * When a piece of a satellite breaks up (hits something), it can turn into one or more fragments and zero or more parts. Each fragment is drawn with drawFragment() where the draw functions for parts is describe above (such as drawCrewDragonLeft()). When a fragment or part is created from the ruins of a satellite or a part of a satellite, it inherits the parent's velocity and adds a kick.
 
 * For example, if a satellite is traveling at (3,000 m/s, 4,000 m/s) (a linear speed of 5,000 m/s) and breaks up, a fragment or part may shoot off at 90° (horizontally to the right where 0° is straight up). Fragments and parts add anywhere between 5,000 m/s and 9,000 m/s to the parent's speed. This means that the the resulting fragment will be traveling between (8,000 m/s, 4,000 m/s) and (12,000 m/s, 4,000 m/s) when it is created.

 * To keep newly created fragments from hitting each other immediately after creation, fragments and parts are placed 4 pixels from their point of creation in the direction of travel. Thus a fragment or part created at (700 px, -300 px) traveling at 180° (straight down) will start its life at (700 px, -296 px).

 * Fragments rotate wildly when they are created. They also retire randomly anywhere from 50 to 100 frames (2-3 seconds of simulator time) after they are created. Each fragment has a radius of 2 pixels.
 * ...
 **************************************************/
std::vector<Satellite *> Satellite::breakIntoFragments() {
   std::vector<Satellite *> newFragments;
   for (int i = 0; i < fragmentAmount; i++)
      newFragments.push_back((Satellite *)new Fragment(p, v, 0.0));
   
   return newFragments;
   
   // Note: although this is a part of the death sequence, we'll let MovingObject*->hit() handle setting alive <- false.
   // same goes for breakIntoParts().
}

/**************************************************
 * Method: Break into Parts
 * Class: GPS
 **************************************************/
std::vector<Satellite *> GPS::breakIntoParts() {
   // initialize
   Position pOffset;
   Velocity vOffset;

   // When a GPS satellite comes into contact with another element in the simulation it breaks up into 3 pieces
   
   // These pieces are:
   
   // The center: drawGPSCenter() at 7 pixels radius
   Satellite * centerPart = new GPS::Center;
   centerPart->addPosition(getPosition());
   centerPart->addVelocity(getVelocity());
   
   // The left solar array drawGPSLeft() at 8 pixel radius
   Satellite * leftPart = new GPS::Left;
   leftPart->addPosition(getPosition());
   leftPart->addVelocity(getVelocity());

   // The right solar array drawGPSLeft() at 8 pixel radius
   Satellite * rightPart = new GPS::Right;
   rightPart->addPosition(getPosition());
   rightPart->addVelocity(getVelocity());

   std::vector<Satellite *> parts;
   parts.push_back(centerPart);
   parts.push_back(leftPart);
   parts.push_back(rightPart);
   return parts;
}

/**************************************************
 * Method: Break into Parts
 * Class: Hubble
 **************************************************/
std::vector<Satellite *> CrewDragon::breakIntoParts()
{
   // initialize
   Position pOffset;
   Velocity vOffset;

   // When a CrewDragon satellite comes into contact with another element in the simulation it breaks up into 3 pieces
   
   // These pieces are:
   
   // The center
   Satellite * centerPart = new CrewDragon::Center;
   centerPart->addPosition(getPosition());
   centerPart->addVelocity(getVelocity());
   
   // The left part
   Satellite * leftPart = new CrewDragon::Left;
   leftPart->addPosition(getPosition());
   leftPart->addVelocity(getVelocity());

   // The right part
   Satellite * rightPart = new CrewDragon::Right;
   rightPart->addPosition(getPosition());
   rightPart->addVelocity(getVelocity());
   
   std::vector<Satellite *> parts;
   parts.push_back(centerPart);
   parts.push_back(leftPart);
   parts.push_back(rightPart);
   return parts;
}
/**************************************************
 * Method: Break into Parts
 * Class: Hubble
 **************************************************/
std::vector<Satellite *> Hubble::breakIntoParts()
{
   // initialize
   Position pOffset;
   Velocity vOffset;

   // When a Hubble satellite comes into contact with another element in the simulation it breaks up into 3 pieces
   
   // These pieces are:
   // The Telescope part
   Satellite * telescope = new Hubble::Telescope;
   telescope->addPosition(getPosition());
   telescope->addVelocity(getVelocity());
   
   // The computer part
   Satellite * computer = new Hubble::Computer;
   computer->addPosition(getPosition());
   computer->addVelocity(getVelocity());
   
   // The left part
   Satellite * leftPart = new Hubble::Left;
   leftPart->addPosition(getPosition());
   leftPart->addVelocity(getVelocity());

   // The right part
   Satellite * rightPart = new Hubble::Right;
   rightPart->addPosition(getPosition());
   rightPart->addVelocity(getVelocity());
   
   std::vector<Satellite *> parts;
   parts.push_back(telescope);
   parts.push_back(computer);
   parts.push_back(leftPart);
   parts.push_back(rightPart);
   return parts;
}
/**************************************************
 * Method: Break into Parts
 * Class: Starlink
 **************************************************/
std::vector<Satellite *> Starlink::breakIntoParts()
{
   // initialize
   Position pOffset;
   Velocity vOffset;

   // When a Hubble satellite comes into contact with another element in the simulation it breaks up into 3 pieces
   
   // These pieces are:
   // The body
   Satellite * body = new Starlink::Body;
   body->addPosition(getPosition());
   body->addVelocity(getVelocity());
   
   // The array
   Satellite * array = new Starlink::Array;
   array->addPosition(getPosition());
   array->addVelocity(getVelocity());
   
   std::vector<Satellite *> parts;
   parts.push_back(body);
   parts.push_back(array);
   return parts;
}
