/*
  task5.h - Library for task #, this .
*/
#ifndef task5_h //Makes sure library is not redefined
#define task5_h

#include "Arduino.h"

class task5
{
    public:
        task5(); //Default constructor
        task5(int echo, int trig, int but, int leds[]); //Constructor needed to properly function
        boolean start(int l1, int l2, int l3, int l4, int l5, int l6); //Start function to start the task
        void setLeds(boolean leds[]); //Helper functions to make repetitive tasks easier.
        int getDistanceSensor();
    private:
        int uEcho, uTrig, button, led1, led2, led3, led4, led5, led6; //Necessary pin numbers
};

#endif