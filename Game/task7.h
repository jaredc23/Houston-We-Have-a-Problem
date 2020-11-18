/*
  task7.h - Library for task #7
*/
#ifndef task7_h //Use this so that the library is never redefined
#define task7_h

#include "Arduino.h"

class task7
{
    public:
        task7(); //Default constructor needed
        task7(int& buzz, int& pot, int rled, int bled, int gled);//Constructor to make object
        boolean start(int tone1, int tone2, int tone3);
    private:
        int buzzer, potentiometer, r, g, b; //Private variables for all the nessesary components
};

#endif