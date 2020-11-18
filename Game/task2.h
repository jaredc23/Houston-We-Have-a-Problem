/*
  task2.h - Library for task 2, this task uses the LEDs, the Servo and the pot.

*/
#ifndef task2_h
#define task2_h //Make sure not to redefine the library

#include "Arduino.h" //Include necessary libraries
#include <Servo.h>

class task2
{
    public:
        task2(); //Default constructor
        task2(int b1, int b2, int b3, int b4, int pot, int leds[]); //Constructor needed to set pin values
        boolean start(boolean led1, boolean led2, boolean led3, boolean led4, boolean led5, boolean led6, int positions, int buttons); //Start function to call the task
    private:
        int but1, but2, but3, but4, potentiometer, l1, l2, l3, l4, l5, l6; //All the variables to store the pin numbers
};

#endif