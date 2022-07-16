/**********************************************************************
 * simulator.cpp
 * orbitSimulator
 *
 * -- Simulator class source code to be placed in this file to simplify
 *    the look of the header file --
 **********************************************************************/

#include "simulator.h"

void Simulator::applyGravity(const Interface * pUI) {
   if (ship.isAlive())
      ship.applyGravity(earth, pUI->getDeltaTime());
   
   for (auto it : satellites)
      if (it->isAlive())
         it->applyGravity(earth, pUI->getDeltaTime());
   
   for (auto it : projectiles)
      if (it.isAlive())
         it.applyGravity(earth, pUI->getDeltaTime());
}


void Simulator::handleCollisions() {
   // ship and satellites
   for (Satellite * satellite : satellites)
      handleCollision(ship, satellite);
   
   // ship and earth
   handleCollision(ship, earth);
   
   // ship and edge of screen
   if (abs(ship.getPosition().getX()) >= tr.getX() ||
         abs(ship.getPosition().getY()) >= tr.getY())
      ship.hit();
   
   // everything to the earth
   for (Satellite * satellite  : satellites)
      handleCollision(earth, satellite);
   
   for (Projectile & projectile : projectiles)
      handleCollision(earth, projectile);
   
   // bullets and moving objects
   for (Projectile & projectile : projectiles)
      for (Satellite * satellite : satellites)
         handleCollision(projectile, satellite);
}

void Simulator::handleCollision(SpaceShip, Earth) {
   if (!ship.isAlive() || !earth.isAlive()) return;
   if (!hasCollided(ship, earth)) return;
   std::cout << "handling collision between ship and earth\n";
   ship.hit();
}

void Simulator::handleCollision(Earth, Projectile & projectile) {
   if (!earth.isAlive() || !projectile.isAlive()) return;
   if (!hasCollided(earth, projectile)) return;
   std::cout << "handling collision between earth and projectile\n";
   projectile.hit();
}

void Simulator::handleCollision(Earth, Satellite * satellite) {
   if (!earth.isAlive() || !satellite->isAlive()) return;
   if (!hasCollided(earth, *satellite)) return;
   std::cout << "handling collision between earth and satellite ("
             << getSatelliteName(satellite) << ")\n";
   satellite->hit();
}

void Simulator::handleCollision(SpaceShip, Satellite* satellite) {
   if (!ship.isAlive() || !satellite->isAlive()) return;
   if (!hasCollided(ship, *satellite)) return;
   std::cout << "handling collision between ship and satellite ("
             << getSatelliteName(satellite) << ")\n";

   // set ship/satellite instances alive to false
   ship.hit();
   satellite->hit();
   
   // break satellites into parts and fragments
   auto newParts = satellite->breakIntoParts();
   // add all items from newParts[] onto satellites[] end
   satellites.insert(
      std::end(satellites),
      std::begin(newParts),
      std::end(newParts)
   );

   auto newFragments = satellite->breakIntoFragments();
   satellites.insert(
      std::end(satellites),
      std::begin(newFragments),
      std::end(newFragments)
   );
}

void Simulator::handleCollision(Projectile & projectile, Satellite * satellite) {
   if (!projectile.isAlive() || !satellite->isAlive()) return;
   if (!hasCollided(projectile, *satellite)) return;
   std::cout << "handling collision between projectile and satellite ("
             << getSatelliteName(satellite) << ")\n";
   
   projectile.hit();
   satellite->hit();
   
   // break satellites into parts and fragments
   auto newParts = satellite->breakIntoParts();
   satellites.insert(
      std::end(satellites),
      std::begin(newParts),
      std::end(newParts)
   );
      
   auto newFragments = satellite->breakIntoFragments();
   satellites.insert(
      std::end(satellites),
      std::begin(newFragments),
      std::end(newFragments)
   );
}

void Simulator::deleteAllSatellites() {
   // idk why you'd need this helper function but it's
   // a great reference for how to correctly unallocate
   // the memory of pointers (they don't fall in the same
   // scope of memory as the other attributes/class variables)
   
   // check to see if there are any satellites left
   // (just check position 0, this will do.)
   if (satellites[0] != NULL) {
      
      // create a Satellite* iterator, set it to point to
      // the first position in satellites
      std::vector<Satellite*>::iterator it = satellites.begin();
      
      while (it != satellites.end()) {
         // normally here we'd increment by calling ++it,
         // but vector::erase will move us through each
         // item in the collection to the end
         
         // dereference the iterator object using * to get the Satellite* pointer
         Satellite* satellite_ptr = *it; // referring to this as (*it) works just fine
         
         // now we have our pointer, which we want to delete:
         if (satellite_ptr != NULL) { // this should always be null
            
            // The first necessary step before we remove the object + its pntr
            // is to delete the object and set its pointer to NULL
            delete satellite_ptr;
            satellite_ptr = NULL;
            
         }
         
         // the next necessary step in removing an object + pntr
         // is to remove its pointer (now NULL) from vector
         it = satellites.erase(it);
         
      }
   }
   
   // call out the haters
   assert(satellites.size() == 0);
   
   // "only YOU can prevent memory leaks!" ("please allocate responsibly")
}


   
void Simulator::cleanUpZombies() {
   cleanUpSatellites();
   cleanUpProjectiles();
}

void Simulator::cleanUpSatellites() {
   std::vector<Satellite*>::iterator it = satellites.begin();
   while (it != satellites.end()) {
      if (!(*it)->isAlive()) {
         
         // unallocate memory
         Satellite* pSIt = *it;
         delete pSIt;
         pSIt = NULL;
         
         // remove from vector and iterate
         it = satellites.erase(it);
      }
      // just keep swimming
      else ++it;
   }
}

void Simulator::cleanUpProjectiles() {
   std::vector<Projectile>::iterator it = projectiles.begin();
   while (it != projectiles.end()) {
      if (!(it->isAlive()))
         it = projectiles.erase(it);
      else ++it;
   }
}

Satellite* Simulator::createGPSObject(Position p, Velocity v) {
   GPS* newGPS = new GPS; // allocate new memory
   newGPS->setPosition(p); // m
   newGPS->setVelocity(v); // m/s
   return newGPS;
}

void Simulator::createGPSObjects() {
   Position initialP;
   Velocity initialV;

   // ( 0.0 m, 26,560,000.0 m) (-3,880.0 m/s, 0.0 m/s)
   initialP.set(0.0, 26560000.0);
   initialV.set(-3880.0, 0.0);
   satellites.push_back(createGPSObject(initialP, initialV));

   // ( 23,001,634.72 m, 13,280,000.0 m) ( -1,940.00 m/s, 3,360.18 m/s)
   initialP.set(23001634.72, 13280000.0);
   initialV.set(-1940.00, 3360.18);
   satellites.push_back(createGPSObject(initialP, initialV));

   // ( 0.0 m, -26,560,000.0 m) ( 3,880.0 m/s, 0.0 m/s)
   initialP.set(0.0, -26560000.0);
   initialV.set(3880.0, 0.0);
   satellites.push_back(createGPSObject(initialP, initialV));

   // (023,001,634.72 m, -13,280,000.0 m)	( 1,940.00 m/s, -3,360.18 m/s)
   initialP.set(023001634.72, -13280000.0);
   initialV.set(1940.00, -3360.18);
   satellites.push_back(createGPSObject(initialP, initialV));

   // (-23,001,634.72 m, 13,280,000.0 m) ( -1,940.00 m/s, -3,360.18 m/s)
   initialP.set(-23001634.72, -13280000.0);
   initialV.set(-1940.00, -3360.18);
   satellites.push_back(createGPSObject(initialP, initialV));
}

Position Simulator::randomPositionOnScreen() const {
   Position p;
   while (distance(p, earth.getPosition()) < earth.getRadius())
      p.set(random(-tr.getMetersX(), tr.getMetersX()),
            random(-tr.getMetersY(), tr.getMetersY()));
   return p;
}


// helper function for callback(): if we want to restart our program in-game
void replaceSimulator(Position tr, Simulator* pSim) {
   Simulator* newSimulator = new Simulator(tr);
   delete pSim; // don't forget to free old memory!
   pSim = newSimulator; // the ol switcheroo
}


