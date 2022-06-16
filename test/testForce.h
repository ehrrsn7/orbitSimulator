//
//  testForce.h
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
      test_add_force();
      test_operator_add();
      test_operator_addonto();
      test_operator_divide();
   }
private:
   void test_default_constructor() {}
   void test_nondefault_Constructor () {}
   void test_assaingment() {}
   void test_copy_constructor() {}
   void test_add_force() {}
   void test_operator_add() {}
   void test_operator_addonto() {}
   void test_operator_divide() {}

};

