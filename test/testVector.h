//
//  testVector.h
//  orbitSimulator
//
//  Created by Eli Jukes on 6/16/22.
//

#pragma once

#include <iostream>
#include "vector.hpp"
#include <cassert>

using namespace std;

class TestForce
{
public:
   void run()
   {
      test_default_constructor();
      test_nondefault_Constructor();
      test_assaingment();
      test_copy_constructor();
      test_add_vector();
      test_operator_add();
      test_operator_addonto();
      
      test_add_xComp();
      test_add_yComp();
      test_magnitude_cal();
      test_magnitude_add();
      test_polarToCart();
   }
private:
   void test_default_constructor() {}
   void test_nondefault_Constructor () {}
   void test_assaingment() {}
   void test_copy_constructor() {}
   void test_add_force() {}
   void test_operator_add() {}
   void test_operator_addonto() {}

   void test_add_xComp() {}
   void test_add_yComp() {}
   void test_magnitude_cal() {}
   void test_magnitude_add() {}
   void test_polarToCart() {}
};
