//
//  testVector.h
//  orbitSimulator
//
//  Created by Eli Jukes on 6/16/22.
//

#pragma once

#include <iostream>
#include "vector.h"
#include <cassert>
#include <limits>

using namespace std;

class TestVector
{
public:
   void run() {
      ZerosTestCase().run();
      OtherTestCase().run();
      UpperEdgeCase().run();
      LowerEdgeCase().run();
   }

   class ZerosTestCase {
   public:
      void run() {
         test_default_constructor();
         test_nondefault_Constructor();
         test_assignment();
         test_copy_constructor();
         
         testGetX();
         testGetY();
         testSetX();
         testSetY();
         testSetXY();
         testSetS();
         testAddX();
         testAddY();
         testAddXY();
         testAddS();
         testGetMagnitude();
         testGetAngleRadians();
         testAngle();
         testSetPolar();
         testSetMagnitude();
         testAddPolar();
         testAddMagnitude();
      }
      
   private:
      
      /********************
       * Constructors
       ********************/
      void test_default_constructor() {
         // setup
         Vector v;
         // exercise
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      void test_nondefault_Constructor () {
         // setup
         Vector v(0, 0);
         // exercise
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      void test_assignment() {
         // setup
         Vector v1(0, 0);
         Vector vCopy = v1;
         // exercise
         // verify
         assert(vCopy.x == 0);
         assert(vCopy.y == 0);
      }  // breakdown
      
      void test_copy_constructor() {
         // setup
         Vector v1(0, 0);
         Vector vCopy(v1);
         // exercise
         // verify
         assert(vCopy.x == 0);
         assert(vCopy.y == 0);
      }  // breakdown

      
      /********************
       * Getters
       ********************/
      // test getX
      void testGetX() {
         // setup
         Vector v(0, 0);
         // exercise
         // verify
         assert(v.getX() == 0);
      }  // breakdown
      
      // test getY
      void testGetY() {
         // setup
         Vector v(0, 0);
         // exercise
         // verify
         assert(v.getY() == 0);
      }  // breakdown
      
      
      /********************
       * Setters
       ********************/
      // test setX
      void testSetX() {
         // setup
         Vector v(0, 0);
         // exercise
         v.setX(0);
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      // test setY
      void testSetY() {
         // setup
         Vector v(0, 0);
         // exercise
         v.setY(0);
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      // test set(x, y)
      void testSetXY() {
         // setup
         Vector v(0, 0);
         // exercise
         v.set(0, 0);
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      // test set(s)
      void testSetS() {
         // setup
         Vector v(0, 0);
         // exercise
         v.set(Vector(0, 0));
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      
      /********************
       * Adders
       ********************/
      // test addX
      void testAddX() {
         // setup
         Vector v(0, 0);
         // exercise
         v.addX(0);
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      // test addY
      void testAddY() {
         // setup
         Vector v(0, 0);
         // exercise
         v.addY(0);
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      // test add(x, y)
      void testAddXY() {
         // setup
         Vector v(0, 0);
         // exercise
         v.add(0, 0);
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      // test add(s)
      void testAddS() {
         // setup
         Vector v(0, 0);
         // exercise
         v.add(Vector(0, 0));
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      /********************
       * Other Getters/Setters
       ********************/
      // test getMagnitude
      void testGetMagnitude() {
         // setup
         Vector v(0, 0);
         // exercise
         // verify
         assert(v.getMagnitude() == 0);
      }  // breakdown
      
      // test getAngleRadians
      void testGetAngleRadians() {
         // setup
         Vector v(0, 0);
         // exercise
         // verify
         assert(v.getAngleRadians() == 0);
      }  // breakdown
      
      // test angle
      void testAngle() {
         // setup
         Vector v(0, 0);
         // exercise
         // verify
         assert(v.angle() == 0);
      }  // breakdown
      
      // test setPolar
      void testSetPolar() {
         // setup
         Vector v(0, 0);
         // exercise
         v.setPolar(0, 0);
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      // test setMagnitude
      void testSetMagnitude() {
         // setup
         Vector v(0, 0);
         // exercise
         v.setMagnitude(0, 0);
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      // test addPolar
      void testAddPolar() {
         // setup
         Vector v(0, 0);
         // exercise
         v.addPolar(0, 0);
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      // test addMagnitude
      void testAddMagnitude() {
         // setup
         Vector v(0, 0);
         // exercise
         v.addMagnitude(0, 0);
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
   };

   class OtherTestCase {
   public:
      void run() {
         test_default_constructor();
         test_nondefault_Constructor();
         test_assignment();
         test_copy_constructor();
         
         testGetX();
         testGetY();
         testSetX();
         testSetY();
         testSetXY();
         testSetS();
         testAddX();
         testAddY();
         testAddXY();
         testAddS();
         testGetMagnitude();
         testGetAngleRadians();
         testAngle();
         testSetPolar();
         testSetMagnitude();
         testAddPolar();
         testAddMagnitude();
      }
      
   private:
      
      /********************
       * Constructors
       ********************/
      void test_default_constructor() {
         // setup
         Vector v;
         // exercise
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      void test_nondefault_Constructor () {
         // setup
         Vector v(2, -5);
         // exercise
         // verify
         assert(v.x == 2);
         assert(v.y == -5);
      }  // breakdown
      
      void test_assignment() {
         // setup
         Vector v1(2, -5);
         Vector vCopy = v1;
         // exercise
         // verify
         assert(vCopy.x == 2);
         assert(vCopy.y == -5);
      }  // breakdown
      
      void test_copy_constructor() {
         // setup
         Vector v1(2, -5);
         Vector vCopy(v1);
         // exercise
         // verify
         assert(vCopy.x == 2);
         assert(vCopy.y == -5);
      }  // breakdown

      
      /********************
       * Getters
       ********************/
      // test getX
      void testGetX() {
         // setup
         Vector v(2, -5);
         // exercise
         // verify
         assert(v.getX() == 2);
      }  // breakdown
      
      // test getY
      void testGetY() {
         // setup
         Vector v(2, -5);
         // exercise
         // verify
         assert(v.getY() == -5);
      }  // breakdown
      
      
      /********************
       * Setters
       ********************/
      // test setX
      void testSetX() {
         // setup
         Vector v(2, -5);
         // exercise
         v.setX(7);
         // verify
         assert(v.x == 7);
         assert(v.y == -5);
      }  // breakdown
      
      // test setY
      void testSetY() {
         // setup
         Vector v(2, -5);
         // exercise
         v.setY(7);
         // verify
         assert(v.x == 2);
         assert(v.y == 7);
      }  // breakdown
      
      // test set(x, y)
      void testSetXY() {
         // setup
         Vector v(2, -5);
         // exercise
         v.set(7, 7);
         // verify
         assert(v.x == 7);
         assert(v.y == 7);
      }  // breakdown
      
      // test set(s)
      void testSetS() {
         // setup
         Vector v(2, -5);
         // exercise
         v.set(Vector(7, 7));
         // verify
         assert(v.x == 7);
         assert(v.y == 7);
      }  // breakdown
      
      
      /********************
       * Adders
       ********************/
      // test addX
      void testAddX() {
         // setup
         Vector v(2, -5);
         // exercise
         v.addX(7);
         // verify
         assert(v.x == 9);
         assert(v.y == -5);
      }  // breakdown
      
      // test addY
      void testAddY() {
         // setup
         Vector v(2, -5);
         // exercise
         v.addY(7);
         // verify
         assert(v.x == 2);
         assert(v.y == 2);
      }  // breakdown
      
      // test add(x, y)
      void testAddXY() {
         // setup
         Vector v(2, -5);
         // exercise
         v.add(7, 7);
         // verify
         assert(v.x == 9);
         assert(v.y == 2);
      }  // breakdown
      
      // test add(s)
      void testAddS() {
         // setup
         Vector v(2, -5);
         // exercise
         v.add(Vector(7, 7));
         // verify
         assert(v.x == 9);
         assert(v.y == 2);
      }  // breakdown
      
      /********************
       * Other Getters/Setters
       ********************/
      // test getMagnitude
      void testGetMagnitude() {
         // setup
         Vector v(2, -5);
         // exercise
         // verify
         assert(v.getMagnitude() == sqrt(2*2 + -5*-5));
      }  // breakdown
      
      // test getAngleRadians
      void testGetAngleRadians() {
         // setup
         Vector v(2, -5);
         // exercise
         // verify
         assert(v.getAngleRadians() == atan2(2, -5));
      }  // breakdown
      
      // test angle
      void testAngle() {
         // setup
         Vector v(2, -5);
         // exercise
         // verify
         assert(v.angle() == atan2(2, -5));
      }  // breakdown
      
      // test setPolar
      void testSetPolar() {
         // setup
         Vector v(2, -5);
         // exercise
         v.setPolar(7, M_PI/3);
         // verify
         assert(v.x == 7 * sin(M_PI/3));
         assert(v.y == 7 * cos(M_PI/3));
      }  // breakdown
      
      // test setMagnitude
      void testSetMagnitude() {
         // setup
         Vector v(2, -5);
         // exercise
         v.setMagnitude(7, M_PI/3);
         // verify
         assert(v.x == 7 * sin(M_PI/3));
         assert(v.y == 7 * cos(M_PI/3));
      }  // breakdown
      
      // test addPolar
      void testAddPolar() {
         // setup
         Vector v(2, -5);
         // exercise
         v.addPolar(7, M_PI/3);
         // verify
         assert(v.x == 2 + 7 * sin(M_PI/3));
         assert(v.y == -5 + 7 * cos(M_PI/3));
      }  // breakdown
      
      // test addMagnitude
      void testAddMagnitude() {
         // setup
         Vector v(2, -5);
         // exercise
         v.addMagnitude(7, M_PI/3);
         // verify
         assert(v.x == 2 + 7 * sin(M_PI/3));
         assert(v.y == -5 + 7 * cos(M_PI/3));
      }  // breakdown
      
   };

   class UpperEdgeCase {
   public:
      void run() {
         test_default_constructor();
         test_nondefault_Constructor();
         test_assignment();
         test_copy_constructor();
         
         testGetX();
         testGetY();
         testSetX();
         testSetY();
         testSetXY();
         testSetS();
         
         // == After careful consideration we decided to not include some edge cases
         
         // testAddX(); // we want these to throw errors. how do we handle this?
         testAddY();
         // testAddXY(); // (the error here is double_max + positive_amount will be negative, which doesn't make sense)
         // testAddS(); // error
         // testGetMagnitude(); // error? we have to have double_max^2 in answer calculation
         testGetAngleRadians();
         testAngle();
         testSetPolar();
         testSetMagnitude();
         // testAddPolar(); // error
         // testAddMagnitude(); // error
      }
      
   private:
      
      /********************
       * Constructors
       ********************/
      void test_default_constructor() {
         // setup
         Vector v;
         // exercise
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      void test_nondefault_Constructor () {
         // setup
         Vector v(numeric_limits<double>::max(), numeric_limits<double>::max());
         // exercise
         // verify
         assert(v.x == numeric_limits<double>::max());
         assert(v.y == numeric_limits<double>::max());
      }  // breakdown
      
      void test_assignment() {
         // setup
         Vector v1(numeric_limits<double>::max(), numeric_limits<double>::max());
         Vector vCopy = v1;
         // exercise
         // verify
         assert(vCopy.x == numeric_limits<double>::max());
         assert(vCopy.y == numeric_limits<double>::max());
      }  // breakdown
      
      void test_copy_constructor() {
         // setup
         Vector v1(numeric_limits<double>::max(), numeric_limits<double>::max());
         Vector vCopy(v1);
         // exercise
         // verify
         assert(vCopy.x == numeric_limits<double>::max());
         assert(vCopy.y == numeric_limits<double>::max());
      }  // breakdown

      
      /********************
       * Getters
       ********************/
      // test getX
      void testGetX() {
         // setup
         Vector v(numeric_limits<double>::max(), numeric_limits<double>::max());
         // exercise
         // verify
         assert(v.getX() == numeric_limits<double>::max());
      }  // breakdown
      
      // test getY
      void testGetY() {
         // setup
         Vector v(numeric_limits<double>::max(), numeric_limits<double>::max());
         // exercise
         // verify
         assert(v.getY() == numeric_limits<double>::max());
      }  // breakdown
      

      /********************
       * Setters
       ********************/
      // test setX
      void testSetX() {
         // setup
         Vector v(2, -5);
         // exercise
         v.setX(numeric_limits<double>::max());
         // verify
         assert(v.x == numeric_limits<double>::max());
         assert(v.y == -5);
      }  // breakdown
      
      // test setY
      void testSetY() {
         // setup
         Vector v(2, -5);
         // exercise
         v.setY(numeric_limits<double>::max());
         // verify
         assert(v.x == 2);
         assert(v.y == numeric_limits<double>::max());
      }  // breakdown
      
      // test set(x, y)
      void testSetXY() {
         // setup
         Vector v(2, -5);
         // exercise
         v.set(numeric_limits<double>::max(), numeric_limits<double>::max());
         // verify
         assert(v.x == numeric_limits<double>::max());
         assert(v.y == numeric_limits<double>::max());
      }  // breakdown
      
      // test set(s)
      void testSetS() {
         // setup
         Vector v(2, -5);
         // exercise
         v.set(Vector(numeric_limits<double>::max(), numeric_limits<double>::max()));
         // verify
         assert(v.x == numeric_limits<double>::max());
         assert(v.y == numeric_limits<double>::max());
      }  // breakdown
      
      
      /********************
       * Adders
       ********************/
      // test addX
      void testAddX() {
         // setup
         Vector v(2, -5);
         // exercise
         v.addX(numeric_limits<double>::max());
         // verify
         assert(v.x == 2 + numeric_limits<double>::max()); // error?
         assert(v.y == -5);
      }  // breakdown
      
      // test addY
      void testAddY() {
         // setup
         Vector v(2, -5);
         // exercise
         v.addY(numeric_limits<double>::max());
         // verify
         assert(v.x == 2);
         assert(v.y == -5 + numeric_limits<double>::max());
      }  // breakdown
      
      // test add(x, y)
      void testAddXY() {
         // setup
         Vector v(2, -5);
         // exercise
         v.add(numeric_limits<double>::max(), numeric_limits<double>::max());
         // verify
         assert(v.x == 2 + numeric_limits<double>::max()); // error?
         assert(v.y == -5 + numeric_limits<double>::max());
      }  // breakdown
      
      // test add(s)
      void testAddS() {
         // setup
         Vector v(2, -5);
         // exercise
         v.add(Vector(numeric_limits<double>::max(), numeric_limits<double>::max()));
         // verify
         assert(v.x == 2 + numeric_limits<double>::max()); // error?
         assert(v.y == -5 + numeric_limits<double>::max());
      }  // breakdown
      
      /********************
       * Other Getters/Setters
       ********************/
      // test getMagnitude
      void testGetMagnitude() {
         // setup
         Vector v(numeric_limits<double>::max(), numeric_limits<double>::max());
         // exercise
         // verify
         assert(v.getMagnitude() == sqrt(pow(numeric_limits<double>::max(), 2) + pow(numeric_limits<double>::max(), 2))); // error?
      }  // breakdown
      
      // test getAngleRadians
      void testGetAngleRadians() {
         // setup
         Vector v(numeric_limits<double>::max(), numeric_limits<double>::max());
         // exercise
         // verify
         assert(v.getAngleRadians() == M_PI/4);
      }  // breakdown
      
      // test angle
      void testAngle() {
         // setup
         Vector v(numeric_limits<double>::max(), numeric_limits<double>::max());
         // exercise
         // verify
         assert(v.angle() == M_PI/4);
      }  // breakdown
      
      // test setPolar
      void testSetPolar() {
         // setup
         Vector v(2, -5);
         // exercise
         v.setPolar(numeric_limits<double>::max(), numeric_limits<double>::max());
         // verify
         assert(v.x == numeric_limits<double>::max() * sin(numeric_limits<double>::max()));
         assert(v.y == numeric_limits<double>::max() * cos(numeric_limits<double>::max()));
      }  // breakdown
      
      // test setMagnitude
      void testSetMagnitude() {
         // setup
         Vector v(2, -5);
         // exercise
         v.setMagnitude(numeric_limits<double>::max(), numeric_limits<double>::max());
         // verify
         assert(v.x == numeric_limits<double>::max() * sin(numeric_limits<double>::max()));
         assert(v.y == numeric_limits<double>::max() * cos(numeric_limits<double>::max()));
      }  // breakdown
      
      // test addPolar
      void testAddPolar() {
         // setup
         Vector v(2, -5);
         // exercise
         v.addPolar(numeric_limits<double>::max(), numeric_limits<double>::max());
         // verify
         assert(v.x == 2 + numeric_limits<double>::max() * sin(numeric_limits<double>::max())); // error?
         assert(v.y == -5 + numeric_limits<double>::max() * cos(numeric_limits<double>::max()));
      }  // breakdown
      
      // test addMagnitude
      void testAddMagnitude() {
         // setup
         Vector v(2, -5);
         // exercise
         v.addMagnitude(numeric_limits<double>::max(), numeric_limits<double>::max());
         // verify
         assert(v.x == 2 + numeric_limits<double>::max() * sin(numeric_limits<double>::max())); // error?
         assert(v.y == -5 + numeric_limits<double>::max() * cos(numeric_limits<double>::max()));
      }  // breakdown
      
   };

   class LowerEdgeCase {
   public:
      void run() {
         test_default_constructor();
         test_nondefault_Constructor();
         test_assignment();
         test_copy_constructor();
         
         testGetX();
         testGetY();
         testSetX();
         testSetY();
         testSetXY();
         testSetS();
         // testAddX(); // we want these to throw errors. how do we handle this?
         testAddY();
         // testAddXY(); // (the error here is double_max + positive_amount will be negative, which doesn't make sense)
         // testAddS(); // error
         // testGetMagnitude(); // error? we have to have double_max^2 in answer calculation
         testGetAngleRadians();
         testAngle();
         testSetPolar();
         testSetMagnitude();
         // testAddPolar(); // error
         // testAddMagnitude(); // error
      }
      
   private:
      
      /********************
       * Constructors
       ********************/
      void test_default_constructor() {
         // setup
         Vector v;
         // exercise
         // verify
         assert(v.x == 0);
         assert(v.y == 0);
      }  // breakdown
      
      void test_nondefault_Constructor () {
         // setup
         Vector v(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
         // exercise
         // verify
         assert(v.x == std::numeric_limits<double>::lowest());
         assert(v.y == std::numeric_limits<double>::lowest());
      }  // breakdown
      
      void test_assignment() {
         // setup
         Vector v1(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
         Vector vCopy = v1;
         // exercise
         // verify
         assert(vCopy.x == std::numeric_limits<double>::lowest());
         assert(vCopy.y == std::numeric_limits<double>::lowest());
      }  // breakdown
      
      void test_copy_constructor() {
         // setup
         Vector v1(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
         Vector vCopy(v1);
         // exercise
         // verify
         assert(vCopy.x == std::numeric_limits<double>::lowest());
         assert(vCopy.y == std::numeric_limits<double>::lowest());
      }  // breakdown

      
      /********************
       * Getters
       ********************/
      // test getX
      void testGetX() {
         // setup
         Vector v(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
         // exercise
         // verify
         assert(v.getX() == std::numeric_limits<double>::lowest());
      }  // breakdown
      
      // test getY
      void testGetY() {
         // setup
         Vector v(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
         // exercise
         // verify
         assert(v.getY() == std::numeric_limits<double>::lowest());
      }  // breakdown
      

      /********************
       * Setters
       ********************/
      // test setX
      void testSetX() {
         // setup
         Vector v(2, -5);
         // exercise
         v.setX(std::numeric_limits<double>::lowest());
         // verify
         assert(v.x == std::numeric_limits<double>::lowest());
         assert(v.y == -5);
      }  // breakdown
      
      // test setY
      void testSetY() {
         // setup
         Vector v(2, -5);
         // exercise
         v.setY(std::numeric_limits<double>::lowest());
         // verify
         assert(v.x == 2);
         assert(v.y == std::numeric_limits<double>::lowest());
      }  // breakdown
      
      // test set(x, y)
      void testSetXY() {
         // setup
         Vector v(2, -5);
         // exercise
         v.set(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
         // verify
         assert(v.x == std::numeric_limits<double>::lowest());
         assert(v.y == std::numeric_limits<double>::lowest());
      }  // breakdown
      
      // test set(s)
      void testSetS() {
         // setup
         Vector v(2, -5);
         // exercise
         v.set(Vector(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest()));
         // verify
         assert(v.x == std::numeric_limits<double>::lowest());
         assert(v.y == std::numeric_limits<double>::lowest());
      }  // breakdown
      
      
      /********************
       * Adders
       ********************/
      // test addX
      void testAddX() {
         // setup
         Vector v(2, -5);
         // exercise
         v.addX(std::numeric_limits<double>::lowest());
         // verify
         assert(v.x == 2 + std::numeric_limits<double>::lowest()); // error?
         assert(v.y == -5);
      }  // breakdown
      
      // test addY
      void testAddY() {
         // setup
         Vector v(2, -5);
         // exercise
         v.addY(std::numeric_limits<double>::lowest());
         // verify
         assert(v.x == 2);
         assert(v.y == -5 + std::numeric_limits<double>::lowest());
      }  // breakdown
      
      // test add(x, y)
      void testAddXY() {
         // setup
         Vector v(2, -5);
         // exercise
         v.add(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
         // verify
         assert(v.x == 2 + std::numeric_limits<double>::lowest()); // error?
         assert(v.y == -5 + std::numeric_limits<double>::lowest());
      }  // breakdown
      
      // test add(s)
      void testAddS() {
         // setup
         Vector v(2, -5);
         // exercise
         v.add(Vector(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest()));
         // verify
         assert(v.x == 2 + std::numeric_limits<double>::lowest()); // error?
         assert(v.y == -5 + std::numeric_limits<double>::lowest());
      }  // breakdown
      
      /********************
       * Other Getters/Setters
       ********************/
      // test getMagnitude
      void testGetMagnitude() {
         // setup
         Vector v(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
         // exercise
         // verify
         assert(v.getMagnitude() == sqrt(pow(std::numeric_limits<double>::lowest(), 2) + pow(std::numeric_limits<double>::lowest(), 2))); // error?
      }  // breakdown
      
      // test getAngleRadians
      void testGetAngleRadians() {
         // setup
         Vector v(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
         // exercise
         // verify
         assert(v.getAngleRadians() == -3 * M_PI/4);
      }  // breakdown
      
      // test angle
      void testAngle() {
         // setup
         Vector v(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
         // exercise
         // verify
         assert(v.angle() == -3 * M_PI/4);
      }  // breakdown
      
      // test setPolar
      void testSetPolar() {
         // setup
         Vector v(2, -5);
         // exercise
         v.setPolar(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
         // verify
         assert(v.x == std::numeric_limits<double>::lowest() * sin(std::numeric_limits<double>::lowest()));
         assert(v.y == std::numeric_limits<double>::lowest() * cos(std::numeric_limits<double>::lowest()));
      }  // breakdown
      
      // test setMagnitude
      void testSetMagnitude() {
         // setup
         Vector v(2, -5);
         // exercise
         v.setMagnitude(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
         // verify
         assert(v.x == std::numeric_limits<double>::lowest() * sin(std::numeric_limits<double>::lowest()));
         assert(v.y == std::numeric_limits<double>::lowest() * cos(std::numeric_limits<double>::lowest()));
      }  // breakdown
      
      // test addPolar
      void testAddPolar() {
         // setup
         Vector v(2, -5);
         // exercise
         v.addPolar(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
         // verify
         assert(v.x == 2 + std::numeric_limits<double>::lowest() * sin(std::numeric_limits<double>::lowest())); // error?
         assert(v.y == -5 + std::numeric_limits<double>::lowest() * cos(std::numeric_limits<double>::lowest()));
      }  // breakdown
      
      // test addMagnitude
      void testAddMagnitude() {
         // setup
         Vector v(2, -5);
         // exercise
         v.addMagnitude(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::lowest());
         // verify
         assert(v.x == 2 + std::numeric_limits<double>::lowest() * sin(std::numeric_limits<double>::lowest())); // error?
         assert(v.y == -5 + std::numeric_limits<double>::lowest() * cos(std::numeric_limits<double>::lowest()));
      }  // breakdown
      
   };

};
