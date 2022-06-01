//
//  simulator.h
//  Lab07
//
//  Created by Elijah Harrison on 5/29/22.
//

#pragma once

#include "uiInteract.h"
#include "uiDraw.h"
#include "geostationarySatellite.h"

class Simulator {
    
public:
   Simulator(Position ptUpperRight) : ptUpperRight(ptUpperRight) {
        earthAngle = 0.0;
    }
    
    void update(const Interface * pUI) {
       earthAngle += 0.01;
//       pDemo->angleShip += 0.02;
//       pDemo->phaseStar++;
       bob.setRelativeP(earthAngle);
       bob.update();
    }
    
    void handleInput(const Interface * pUI) {
        
    }
    
    void display() const {
       drawEarth(earthPosition, earthAngle);
       bob.display();
    }
    
private:
    Position earthPosition;
   Position ptUpperRight;
    double earthAngle;
    GeostationarySatellite bob;
    
    
};
