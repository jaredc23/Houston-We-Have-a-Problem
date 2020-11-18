/*
  task1.h - Library for task 1, this is the Simon Says task.
*/
#ifndef task_h
#define task_h //This is so the library does not redefine itself

#include "Arduino.h"

class task1
{
    public:
        task1(); //Default constructor
        task1(int& b1, int& b2, int& b3, int& b4); //Constructor containing each button
        boolean start(int a, int b, int c, int d, int e, int f); //Start method, each number correlates to the button order
    private:
        int but1, but2, but3, but4; //Necessary pin numbers to function properly
};

#endif