/**********************************************************************
 * main.cpp
 * orbitSimulator
 *
 * Summary:
 *      Simulate satellites orbiting the earth
 **********************************************************************/

#define YEET 0

#include "simulator.h"  // for Simulator
#include "position.h"   // for Point
#include "uiInteract.h" // for Interface
#include "uiDraw.h"     // for Random and draw*

#include <cassert>      // for ASSERT
using namespace std;

/**************************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************************/
void callBack(const Interface* pUI, void* p) {
   // the first step is to cast the void pointer into
   // a game object. This is the first step of every
   // single callback function in OpenGL.
   Simulator* pSim = (Simulator*)p;
   
   pSim->update(pUI);
   pSim->handleInput(pUI);
   pSim->display();
}

double Position::metersFromPixels = 40.0;

/**************************************************
 * Initialize the simulation and set it in motion
 **************************************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   
   // create interface object
   Interface ui(0, NULL,
      "Orbit Simulator", // name on the window
      ptUpperRight);
   
   // create orbit simulator
   Simulator sim(ptUpperRight);
   
   // run interface, pass in orbit simulator
   ui.run(callBack, &sim);

   return YEET;
}
