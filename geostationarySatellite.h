//
//  geostationarySatellite.hpp
//  orbitSimulator
//
//  Created by Elijah Harrison on 5/31/22.
//

#pragma once

#include <iostream>
#include "physics components/position.h"
#include "uiDraw.h"
#include <cmath>

class GeostationarySatellite {
public:
    GeostationarySatellite() {
        angle = 0.0;
    }
    
    void update() {
        angle += 0.02;
    }
    void handleInput() {
        return;
    }
    void display() const
    {
        drawHubble(P, angle);
    }
    Position getP() const { return P;}
//    void setP(Position & p) const { P = p; }
    void setRelativeP(double earthAngle)
    {
        double distanceMeters = 200000;
        double distX = distanceMeters * cos(earthAngle);
        double distY = distanceMeters * sin(earthAngle);
        
        P.setMetersX(distX);
        P.setMetersY(distY);
        
    }
private:
    double angle;
    Position P;
    
};
