/**********************************************************************
 * satellites.h
 * orbitSimulator
 **********************************************************************/


#pragma once

#include "movingObject.h"
#include "uiDraw.h"     // for draw sattelites functions
#include "uiInteract.h" // for user Ship Interface methods
#include <vector>       // i wonder what it could be

#define GPS_MASS 1630
#define SPUTNIK_MASS 83.6
#define HUBBLE_MASS 12246
#define CREWDRAGON_MASS 12055
#define STARLINK_MASS 260

// forward declaration prototypes
class SatellitePart;
class Fragment;

/**************************************************
 * Satellite (Parent Class)
 **************************************************/
class Satellite : public MovingObject {
public:
   Satellite() : fragmentAmount(0) {
      dAngle = 0.001;
   }
   
   ~Satellite() { }
   
   // helper method for Simulator (disabled if fragmentAmount == 0)
   // When a piece of a satellite breaks up (hits something), it can turn into one or more fragments and zero or more parts.
   std::vector<Satellite *> breakIntoFragments();
   
   // different satellites break into parts differently, hence the virtual keyword
   virtual std::vector<Satellite *> breakIntoParts() {
      return std::vector<Satellite *> ();// default: empty vector
   }
   
protected:
   // number of fragments that the Satellite will split into
   int fragmentAmount;
};

/**************************************************
 * Satellite — Children Classes
 * Note: if the set amount of instances is not equal to one, we will have the Simulator class initialize the Position/Velocity for each object.
 * If not, we'll keep things simple and instantiate them here.
 **************************************************/

/**************************************************
 * Satellite Part
 * Our satellites break into Parts just like they break into Fragments.
 * They essentially behave just like satellites.
 **************************************************/
class SatellitePart : public Satellite {
   // fragmentAmount/mass will vary depending on what part it is/what satellite it came from
   // this will not return other satellite parts (inherit from parent)
   
public:
   SatellitePart() {
      // parts rotate wildly after a collision (on construction, in this case)
      setDAngle(random(-M_PI/4, M_PI/4)); // rad/s
      p.addPolar(pixelsToMeters(4)  /* px */,  random(-M_PI, M_PI));
      v.addPolar(random(5000, 9000) /* m/s */, random(-M_PI, M_PI));
   }
};

/**************************************************
 * Sputnik
 * Sputnik was the first satellite, launched on the 4th of October, 1957. The orbit was highly elliptical (non-circular), taking 96.2 minutes to complete each orbit. At the lowest point in its orbit, it is approximately 2,000 km above the earths surface and traveling at 8.1km/s.
 
 * Unfortunately, we cannot simulate the Sputnik orbit because it is too close to the earth. To scale, Sputnick would be about a pixel from the earth's surface, well within the diameter of our not-to-scale graphics. We will place our Sputnik in a elliptical, retrograde (opposite the spin of the earth) orbit. This means that the initial position is at (-36,515,095.13 m, 21,082,000.0 m) and the initial velocity is (2,050.0 m/s, 2,684.68 m/s).
 
 * Sputnik can be drawn with the function drawSputnik().
 * The radius of Sputnik is going to be 4 pixels, drawn not to scale.
 * The actual satellite is 0.058m in diameter, taking 0.00000045 pixels.
 * In other words, our Sputnik will be drawn 10 million times bigger than it should be!
 * When Sputnik comes into contact with another element in the simulation it breaks up into 4 fragments.
 **************************************************/
class Sputnik : public Satellite {
public:
   Sputnik() {
      p.set(-36515095.13, 21082000.0); // m
      v.set(2050.0, 2684.68); // m/s
      fragmentAmount = 4;
      setRadius(pixelsToMeters(4)); // px
      setMass(SPUTNIK_MASS); // kg
   }

   void display() const override {
      MovingObject::display();
      drawSputnik(p, angle);
   }
   
   // Sputnik only drops fragments -- no breakIntoParts implementation
};

/**************************************************
 * GPS
 * The first Global Positioning System (GPS) satellite was launched on the 22nd of February, 1978.
 * At any given moment in time, there are at least 24 GPS satellites orbiting the earth, though there have been a total of 72 launches.
 * The other 48 have since been de-orbited.
 * Each GPS satellite orbits at 20,180km above the earth on a 11 hour 58 minute orbit. Each orbit has a speed of 3.9 km/s.
 * There are six GPS satellites in a given orbit.

 * In our simulation, these will be at the following positions and velocities:

 * Position   Velocity
 * ( 0.0 m, 26,560,000.0 m)   (-3,880.0 m/s, 0.0 m/s)
 * ( 23,001,634.72 m, 13,280,000.0 m)   ( -1,940.00 m/s, 3,360.18 m/s)
 * ( 23,001,634.72 m, -13,280,000.0 m)   ( 1,940.00 m/s, 3,360.18 m/s)
 * ( 0.0 m, -26,560,000.0 m)   ( 3,880.0 m/s, 0.0 m/s)
 * (023,001,634.72 m, -13,280,000.0 m)   ( 1,940.00 m/s, -3,360.18 m/s)
 * (-23,001,634.72 m, 13,280,000.0 m)   ( -1,940.00 m/s, -3,360.18 m/s)
  
 * A GPS satellite can be drawn with the function drawGPS(). The actual size of a GPS satellite is a 2.49m square but the solar array extends several meters to each side. For the purpose of this simulation, we will assume the radius is 12 pixels. When a GPS satellite comes into contact with another element in the simulation it breaks up into 3 pieces and 2 fragments. These pieces are:
 
 * The center: drawGPSCenter() at 7 pixels radius
 * The left solar array drawGPSLeft() at 8 pixel radius
 * The right solar array drawGPSLeft() at 8 pixel radius

 * Each individual piece will then break into 3 fragments if they come into contact with something.
 
 * Amount: 5 (initialize pos/vel in Simulator)
 **************************************************/
class GPS : public Satellite {
public:
   GPS() {
      setRadius(pixelsToMeters(12)); // px
      this->fragmentAmount = 2;
      setMass(GPS_MASS); // kg
   }
   
   void display() const override {
      MovingObject::display();
      drawGPS(p, angle);
   }
   
   std::vector<Satellite *> breakIntoParts() override;

protected:
   class Center;
   class Left;
   class Right;
};

/**************************************************
 * NESTED CLASS
 * GPS::Center Solar Array
 *
 * After the GPS breaks apart, we need to separate it
 * from the GPS and have it act as its own component.
 *
 * "The center: drawGPSCenter() at 7 pixels radius"
 * "Each individual piece will then break into 3
 * fragments if they come into contact with something."
 **************************************************/
class GPS::Center : public SatellitePart {
public:
   Center() {
      setRadius(pixelsToMeters(7)); // px
      this->fragmentAmount = 3;
      setMass(GPS_MASS / 3); // kg
   }
   
   void display() const override {
      MovingObject::display();
      drawGPSCenter(p, angle);
   }
};

/**************************************************
 * NESTED CLASS
 * GPS::Left Solar Array
 *
 * "The left solar array drawGPSLeft() at 8 pixel radius"
 * "Each individual piece will then break into 3
 * fragments if they come into contact with something.
 **************************************************/
class GPS::Left : public SatellitePart {
public:
   Left() {
      setRadius(Position().metersToPixels(8));
      this->fragmentAmount = 3;
      setMass(GPS_MASS / 3); // kg
   }
   
   void display() const override {
      MovingObject::display();
      drawGPSLeft(p, offset, angle);
   }
   
private:
   Position offset;
};

/**************************************************
 * NESTED CLASS
 * GPS::Right Solar Array
 *
 * "The right solar array drawGPSLeft() at 8 pixel radius"
 * "Each individual piece will then break into 3
 * fragments if they come into contact with something."
 **************************************************/
class GPS::Right : public SatellitePart {
public:
   Right() {
      setRadius(pixelsToMeters(8));
      this->fragmentAmount = 3;
      setMass(GPS_MASS / 3); // kg
   }
   
   void display() const override {
      MovingObject::display();
      drawGPSLeft(p, offset, angle);
   }
   
private:
   Position offset;
};

/**************************************************
 * Hubble
 * The Hubble Space Telescope was launched into orbit on the 24th of April, 1990. Though the telescope was placed in low earth orbit, we will place it in GEO for our simulation. This means it is at 35,786.0 km above the earth (42,164 km from the center of the earth). The orbital velocity is 3.1 km/s. We will start with the telescope at (0.0 m, -42,164,000.0 m) with a velocity of (3,100.0 m/s, 0.0 m/s).
 
 * The Hubble space telescope can be drawn with the function drawHubble(). The radius of Hubble is going to be 10 pixels. When Hubble comes into contact with another element in the simulation it breaks up into 4 pieces:

 * The telescope drawHubbleTelescope() at 10 pixels radius and breaking into 3 fragments
 * The computer module drawHubbleComputer() at 7 pixel radius and breaking into 2 fragments
 * The left solar array drawHubbleLeft() at 8 pixel radius and breaking into 2 fragments
 * The right solar array drawHubbleRight() at 8 pixel radius and breaking into 2 fragments
 
 * Amount: 1
 **************************************************/
class Hubble : public Satellite {
public:
   Hubble() {
      p.set(0.0, -42164000.0); // m
      v.set(3100.0, 0.0); // m/s
      fragmentAmount = 3;
      setRadius(pixelsToMeters(10)); // px
      setMass(HUBBLE_MASS); // kg
   }

   void display() const override {
      MovingObject::display();
      drawHubble(p, angle);
   }
   
   std::vector<Satellite *> breakIntoParts() override;
   
protected:
   class Telescope;
   class Computer;
   class Left;
   class Right;
};

/**************************************************
 * NESTED CLASS
 * Hubble::Telescope
 *
 * "The telescope drawHubbleTelescope() at 10 pixels
 * radius and breaking into 3 fragments"
 **************************************************/
class Hubble::Telescope : public SatellitePart {
public:
   Telescope() {
      setRadius(pixelsToMeters(10));
      this->fragmentAmount = 3;
      setMass(HUBBLE_MASS / 4);
   }
   
   void display() const override {
      MovingObject::display();
      drawHubbleTelescope(p, offset, angle);
   }
      
private:
   Position offset;
};

/**************************************************
 * NESTED CLASS
 * Hubble::Computer Module
 *
 * "The computer module drawHubbleComputer() at 7
 * pixel radius and breaking into 2 fragments"
 **************************************************/
class Hubble::Computer : public SatellitePart {
public:
   Computer() {
      setRadius(pixelsToMeters(7));
      this->fragmentAmount = 2;
      setMass(HUBBLE_MASS / 4);
   }
   
   void display() const override {
      MovingObject::display();
      drawHubbleComputer(p, offset, angle);
   }
      
private:
   Position offset;
};

/**************************************************
 * NESTED CLASS
 * Hubble::Left Solar Array
 *
 * "The left solar array drawHubbleLeft() at 8 pixel
 * radius and breaking into 2 fragments"
 **************************************************/
class Hubble::Left : public SatellitePart {
public:
   Left() {
      setRadius(pixelsToMeters(8));
      this->fragmentAmount = 2;
      setMass(HUBBLE_MASS / 4);
   }
   
   void display() const override {
      MovingObject::display();
      drawHubbleLeft(p, offset, angle);
   }
      
private:
   Position offset;
};

/**************************************************
 * NESTED CLASS
 * Hubble::Right Solar Array
 *
 * "The right solar array drawHubbleRight() at 8 pixel
 * radius and breaking into 2 fragments"
 **************************************************/
class Hubble::Right : public SatellitePart {
public:
   Right() {
      setRadius(pixelsToMeters(8));
      this->fragmentAmount = 2;
      setMass(HUBBLE_MASS / 4);
   }
   
   void display() const override {
      MovingObject::display();
      drawHubbleRight(p, offset, angle);
   }
      
private:
   Position offset;
};

/**************************************************
 * SpaceX Crew Dragon
 *
 * The Space X Crew Dragon is part of America's initiative to launch astronauts back into space. We will put this satellite in a low earth orbit at (0.0 m, 8,000,000.0 m) with a velocity of (-7,900.0 m/s, 0.0 m/s).
 
 * The Crew Dragon can be drawn with the function drawCrewDragon(). The radius of Dragon is going to be 7 pixels. When the Crew Dragon comes into contact with another element in the simulation it breaks up into 3 pieces and 2 fragments.

 * The center drawCrewDragonCenter() at 6 pixels radius and breaking into 4 fragments
 * The left solar array drawCrewDragonLeft() at 6 pixel radius and breaking into 2 fragments
 * The right solar array drawGPSLeft() at 6 pixel radius and breaking into 2 fragments
 *
 * Amount: 1
 **************************************************/
class CrewDragon : public Satellite {
public:
   CrewDragon() {
      setPosition(Position(0.0, 8000000.0)); // m
      setVelocity(Velocity(-7900.0, 0.0)); // m/s
      fragmentAmount = 2;
      setRadius(pixelsToMeters(7)); // px
      setMass(CREWDRAGON_MASS); // kg
   }
   
   void display() const override {
      MovingObject::display();
      drawCrewDragon(p, angle);
   }
   
   std::vector<Satellite *> breakIntoParts() override;

protected:
   class Center;
   class Right;
   class Left;
};

/**************************************************
 * NESTED CLASS
 * CrewDragon::Center
 *
 * "The center drawCrewDragonCenter() at 6 pixels
 * radius and breaking into 4 fragments"
 **************************************************/
class CrewDragon::Center : public SatellitePart {
public:
   Center() {
      setRadius(pixelsToMeters(6));
      this->fragmentAmount = 4;
      setMass(CREWDRAGON_MASS / 3);
   }
   
   void display() const override {
      MovingObject::display();
      drawCrewDragonCenter(p, angle);
   }
      
private:
   Position offset;
};

/**************************************************
 * NESTED CLASS
 * CrewDragon::Left Solar Array
 *
 * "The left solar array drawCrewDragonLeft() at 6
 * pixel radius and breaking into 2 fragments"
 **************************************************/
class CrewDragon::Left : public SatellitePart {
public:
   Left() {
      setRadius(pixelsToMeters(6));
      this->fragmentAmount = 2;
      setMass(CREWDRAGON_MASS / 3);
   }
   
   void display() const override {
      MovingObject::display();
      drawCrewDragonLeft(p, offset, angle);
   }
      
private:
   Position offset;
};

/**************************************************
 * NESTED CLASS
 * CrewDragon::Right Solar Array
 *
 * "The right solar array drawGPSLeft() at 6 pixel
 * radius and breaking into 2 fragments"
 **************************************************/
class CrewDragon::Right : public SatellitePart {
public:
   Right() {
      setRadius(pixelsToMeters(6));
      this->fragmentAmount = 2;
      setMass(CREWDRAGON_MASS / 3);
   }
   
   void display() const override {
      MovingObject::display();
      drawCrewDragonRight(p, offset, angle);
   }
      
private:
   Position offset;
};

/**************************************************
 * SpaceX Starlink
 
 * The Space X Starlink satellite is part a larger constellation of satellites that will eventually consist of more than 42,000 members. The first 2 satellites were launched on the 22nd of February, 2018 with a second set of 60 on the 24th of May, 2019. Each of these satellites are in very low earth orbit, meaning they are just 550 km above the surface of the earth. This puts the distance of each satellite at 3 pixels above the earth; too close for our simulation. We will therefore put our Starlink satellite at (0.0 m, -13,020,000.0 m) with a velocity of (5,800.0 m/s, 0.0 m/s).
 
 * The Starlink can be drawn with the function drawStarlink(). The radius of the satellite is 6 pixels. When a Starlink comes into contact with another element in the simulation it breaks up into 2 pieces and 2 fragments.

 * The body drawStarlinkBody() at 2 pixels radius and breaking into 3 fragments
 * The right solar array drawStarlinkArray() at 4 pixel radius and breaking into 3 fragments
 
 * Amount: 1
 **************************************************/
class Starlink : public Satellite {
public:
   Starlink() {
      p.set(0.0, -13020000.0); // m
      v.set(5800.0, 0.0); // m/s
      fragmentAmount = 2;
      setRadius(pixelsToMeters(6)); // px
      setMass(STARLINK_MASS); // kg
   }
   
   void display() const override {
      MovingObject::display();
      drawStarlink(p, angle);
   }
   
   std::vector<Satellite *> breakIntoParts() override;

protected:
   // parts
   class Body;
   class Array;
};

/**************************************************
 * NESTED CLASS
 * Starlink::Body
 *
 * "The body drawStarlinkBody() at 2 pixels radius
 * and breaking into 3 fragments"
 **************************************************/
class Starlink::Body : public SatellitePart {
public:
   Body() {
      setRadius(pixelsToMeters(2));
      this->fragmentAmount = 3;
      setMass(STARLINK_MASS / 2);
   }
   
   void display() const override {
      MovingObject::display();
      drawStarlinkBody(p, offset, angle);
   }
   
private:
   Position offset;
};

/**************************************************
 * NESTED CLASS
 * Starlink::Right Solar Array
 *
 * "The right solar array drawStarlinkArray() at 4
 * pixel radius and breaking into 3 fragments"
 **************************************************/
class Starlink::Array : public SatellitePart {
public:
   Array() {
      setRadius(pixelsToMeters(4));
      this->fragmentAmount = 3;
      setMass(STARLINK_MASS / 2);
   }
   
   void display() const override {
      MovingObject::display();
      drawStarlinkArray(p, offset, angle);
   }
   
private:
   Position offset;
};

/**************************************************
 * Fragment
 * When a piece of a satellite breaks up (hits something), it can turn into one or more fragments and zero or more parts. Each fragment is drawn with drawFragment() where the draw functions for parts is describe above (such as drawCrewDragonLeft()). When a fragment or part is created from the ruins of a satellite or a part of a satellite, it inherits the parent's velocity and adds a kick.

 * For example, if a satellite is traveling at (3,000 m/s, 4,000 m/s) (a linear speed of 5,000 m/s) and breaks up, a fragment or part may shoot off at 90° (horizontally to the right where 0° is straight up). Fragments and parts add anywhere between 5,000 m/s and 9,000 m/s to the parent's speed. This means that the the resulting fragment will be traveling between (8,000 m/s, 4,000 m/s) and (12,000 m/s, 4,000 m/s) when it is created.

 * To keep newly created fragments from hitting each other immediately after creation, fragments and parts are placed 4 pixels from their point of creation in the direction of travel. Thus a fragment or part created at (700 px, -300 px) traveling at 180° (straight down) will start its life at (700 px, -296 px).

 * Fragments rotate wildly when they are created. They also retire randomly anywhere from 50 to 100 frames (2-3 seconds of simulator time) after they are created. Each fragment has a radius of 2 pixels.
 **************************************************/
class Fragment : public Satellite {
public:
   Fragment(Position parentP, Velocity parentV, double collisionAngle) {
      setPosition(parentP);
      setVelocity(parentV);
      setRadius(pixelsToMeters(2)); // px
      setAngle(collisionAngle + random(-0.5 * M_PI, 0.5 * M_PI)); // rad
      setDAngle(random(-2 * M_PI, 2 * M_PI)); // rad/s
      setMass(5); // kg
      
      // fragments rotate wildly when they are created
      expirationTime = random(2, 3); // s
      
      // fragments and parts inherit their parents' velocity and add a kick
      // (anywhere between 5,000 m/s and 9,000 m/s)
      v.addPolar(random(5000, 9000) /* m/s */, angle);
      
      // fragments and parts are placed 4 pixels from their point of
      //creation -- in the direction of travel -- so they don't collide
      // into each other
      p.addPolar(pixelsToMeters(4), angle);
   }
   
   void display() const override {
      MovingObject::display();
      drawFragment(p, angle);
   }
   
   void update(const Interface * pUI) override {
      MovingObject::update(pUI);
      if (expirationTime > 0) expirationTime -= pUI->getDeltaTime();
      else{
         setAlive(false);}
   }
   
private:
   double expirationTime;
};
