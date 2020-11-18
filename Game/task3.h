/*
  task3.h - Library for task 3, this uses LEDs and Servo.
*/
#ifndef task3_h
#define task3_h //Make sure the library is not redefined

#include "Arduino.h"

class task3
{
    public:
        task3(); //Default constructor
        task3(int leds[]); //Constructor needed to run the task
        boolean start(int values[]); //Values represents what to turn on. If it is 0-5, turn on corresponding LED. if it is 6+, go to Servo position 6-#
    private:
        int l1, l2, l3, l4, l5, l6; //Necessary pins needed to function
};

#endif