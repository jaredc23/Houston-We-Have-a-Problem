/*
  task6.h - Library for task 6, this uses the LEDs, servo and buttons.
*/
#ifndef task6_h
#define task6_h //This is so the library is not redefined

#include "Arduino.h"

class task6
{
    public:
        task6(); //Default constructor
        task6(int leds[], int b1); //Constructor
        boolean start(int s1, int s2, int s3, int s4, int s5, int s6, int led1, int led2, int led3, int led4, int led5, int led6); //Start method to call the task
        void setLeds(boolean leds[]); //Helper function to turn on the leds
    private:
        int l1,l2,l3,l4,l5,l6,but1; //All the variables needed to properly function
};

#endif