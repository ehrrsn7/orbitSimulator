//
//  vector.cpp
//  Lab07
//
//  Created by Elijah Harrison on 5/29/22.
//

#include "vector.h"

double Vector::magnitude() const {
   return sqrt((x*x) + (y*y));
}
