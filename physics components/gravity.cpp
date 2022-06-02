//
//  gravity.cpp
//  orbitSimulator
//
//  Created by Elijah Harrison on 5/29/22.
//

#include "physicsComponents.h"

#define ACCEL_DUE_TO_GRAVITY 9.8 // m/s/s

/*********************************************
 * STATICS
 *********************************************/

double Gravity::g = ACCEL_DUE_TO_GRAVITY; // macro defined in "physicsComponents.h"
