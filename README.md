# README

## Orbit Simulator

## CSE 231 — BYU-I
Labs 7-13

### Source code author: James Helfrich
### Instructor: 
## Eli Jukes + Elijah Harrison

tab spaces: 3

Configured to run via XCode or Visual Studio IDEs.

This program will simulate orbital movement around the earth. The speed of the orbiting objects will be sped up. Per the prompt instructions: "One minute in our simulator will be the same as one day in the real world."

![orbit program screenshot](https://content.byui.edu/file/db68eb5b-7b8e-42ad-abd1-b1a2aca17374/1/Ponder/231.07.Ponder.Debris.jpg)

## TODO

- velocity and acceleration are not implemented. For this week's lab (lab 7) we need to implement those.
- note that this creates a design shift. There are no "satellite" or any object classes for that matter. We could continue the same deal, but it would be best for the individual object classes to have a (add velocity) and all the different force interaction methods so that we can write the code for them and just call obj->add gravity, etc. on each one. It's also smart so that we can set the initial velocity in the constructor of each of the classes rather than have a long pile of inits in the Demo constructor and all that. 
- Change Demo class name to something else? I think Simulation or something else could be a cooler name 

