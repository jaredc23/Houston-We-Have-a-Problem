/*
  task4.h - Library for task 4, this is the system calibration task with the ultrasonic sensor and rbg led.
*/
#ifndef task4_h
#define task4_h //Makes sure the library is not redefined

#include "Arduino.h" //Needs to be included in order to access certain functions and constants

class task4
{
    public:
        task4(); //Default constructor
        task4(int& echo, int& trig, int& r1, int& g1, int& b1, int& but); //Constructor needed to function
        boolean start(int distance); //Start function, takes one distance at a time
        int getDistanceSensor(); //Helper function to get distance
    private:
        int uEcho, uTrig, r, g, b, button; //Necessary variables to know pin numbers
};

#endif