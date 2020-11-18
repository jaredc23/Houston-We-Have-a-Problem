/*
  task1.cpp - Library for task 1.
*/

#include "Arduino.h"
#include "task1.h"
#include "Game.h"



task1::task1() {} //We do not need this constructor but it must be coded so here it is

task1::task1(int& b1, int& b2, int& b3, int& b4)  //Initializes the task with the necessary components
{
    but1 = b1;
    but2 = b2;
    but3 = b3;
    but4 = b4;
}

boolean task1::start(int a, int b, int c, int d, int e, int f)//This method starts the actual task using the information provided as the correct answer to the task
{
    for (int i = 1; i <= 6; i++) { //Six times
        if (i == 1) { //Wait for buttons for each round and check if they are all correct
            int b1 = Game::waitForButtons();
            if (b1 != a)
                return false;
            else
                Game::ringBuzzer(200);
        } else if (i == 2) { //Wait for buttons for each round and check if they are all correct
            int b1 = Game::waitForButtons();
            int b2 = Game::waitForButtons();
            if (b1 != a || b2 != b)
                return false;
            else
                Game::ringBuzzer(200);
        } else if (i == 3) {//Wait for buttons for each round and check if they are all correct
            int b1 = Game::waitForButtons();
            int b2 = Game::waitForButtons();
            int b3 = Game::waitForButtons();
            if (b1 != a || b2 != b || b3 != c)
                return false;
            else
                Game::ringBuzzer(200);
        } else if (i == 4) {//Wait for buttons for each round and check if they are all correct
            int b1 = Game::waitForButtons();
            int b2 = Game::waitForButtons();
            int b3 = Game::waitForButtons();
            int b4 = Game::waitForButtons();
            if (b1 != a || b2 != b || b3 != c || b4 != d)
                return false;
            else
                Game::ringBuzzer(200);
        } else if (i == 5) {//Wait for buttons for each round and check if they are all correct
            int b1 = Game::waitForButtons();
            int b2 = Game::waitForButtons();
            int b3 = Game::waitForButtons();
            int b4 = Game::waitForButtons();
            int b5 = Game::waitForButtons();
            if (b1 != a || b2 != b || b3 != c || b4 != d || b5 != e)
                return false;
            else
                Game::ringBuzzer(200);
        } else if (i == 6) {//Wait for buttons for each round and check if they are all correct
            int b1 = Game::waitForButtons();
            int b2 = Game::waitForButtons();
            int b3 = Game::waitForButtons();
            int b4 = Game::waitForButtons();
            int b5 = Game::waitForButtons();
            int b6 = Game::waitForButtons();
            if (b1 != a || b2 != b || b3 != c || b4 != d || b5 != e || b6 != f)
                return false;
            else
                Game::ringBuzzer(200);
        }

    }
    return true;
}
