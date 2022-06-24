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
std::vector<Fragment> Satellite::breakIntoFragments() {
   std::vector<Fragment> newFragments;
   for (int i = 0; i < fragmentAmount; i++)
      newFragments.push_back(Fragment(p, v, 0.0));
   // let Fragment Constructor randomize v
   
   return newFragments;
   
   // Note: although this is a part of the death sequence, we'll let MovingObject*->hit() handle setting alive <- false.
   // same goes for breakIntoParts().
}

/**************************************************
 * Method: Break into Parts
 * Class: GPS
 **************************************************/
std::vector<SatellitePart> GPS::breakIntoParts() {
   // When a GPS satellite comes into contact with another element in the simulation it breaks up into 3 pieces
   std::vector<SatellitePart> parts;
   Position center = this->getPosition();
   
   // These pieces are:
   
   // The center: drawGPSCenter() at 7 pixels radius
   GPSCenter pieceCenter; // (offset code copied from uiDraw.h)
   pieceCenter.setPosition(center);
   pieceCenter.setRadius(Position().pixelsToMeters(7)); // px
   parts.push_back(pieceCenter);
   
   // The left solar array drawGPSLeft() at 8 pixel radius
   GPSLeft pieceLeft;
   Position posLeft;
   posLeft.setPixelsX(0.0);
   posLeft.setPixelsY(12.0);
   pieceLeft.setOffset(posLeft);
   posLeft.addPolar(center.getMagnitude(), this->angle);
   pieceLeft.setPosition(posLeft);
   pieceLeft.setRotation(getAngle());
   pieceCenter.setRadius(Position().pixelsToMeters(8)); // px
   parts.push_back(pieceLeft);
   
   // The right solar array drawGPSLeft() at 8 pixel radius
   GPSRight pieceRight;
   Position posRight;
   posRight.setPixelsX(0.0);
   posRight.setPixelsY(12.0);
   pieceRight.setOffset(posRight);
   posRight.addPolar(center.getMagnitude(), this->angle);
   pieceRight.setPosition(posRight);
   pieceRight.setRotation(getAngle());
   pieceCenter.setRadius(Position().pixelsToMeters(8)); // px
   parts.push_back(pieceRight);
   
   return parts;
}
