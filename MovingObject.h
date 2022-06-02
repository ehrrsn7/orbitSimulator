//
//  MovingObject.hpp
//  orbitSimulator
//
//  Created by Elijah Harrison on 5/29/22.
//

#pragma once

/*********************************************
 * CLASS Moving Object
 * Parent of all of the objects that have
 * mass, position and velocity.
 *********************************************/
class MovingObject {
    
public:
    // constructors
    
    // mass
    void setMass(double mass) { m = mass; }
    double getMass() const { return m; }

private:
    double m; // mass (kg)
    // Position p;
    // Velocity v;
    // what do we put here? if it's all purely a has-a relationship then we should put all the possible physics child classes as MovingObject components
};

class Hubble : MovingObject {};
