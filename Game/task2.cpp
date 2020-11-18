/*
  task2.cpp - Library for task 2.
*/

#include "Arduino.h"
#include "task2.h"
#include "Game.h"


task2::task2() {}

task2::task2(int b1, int b2, int b3, int b4, int pot, int leds[]) //Initializes the task with the necessary components
{
    but1 = b1;
    but2 = b2;
    but3 = b3;
    but4 = b4;
    potentiometer = pot;
    l1 = leds[0];
    l2 = leds[1];
    l3 = leds[2];
    l4 = leds[3];
    l5 = leds[4];
    l6 = leds[5];
}

boolean task2::start(boolean led1, boolean led2, boolean led3, boolean led4, boolean led5, boolean led6, int positions, int buttons) //This method starts the actual task using the information provided as the correct answer to the task
{
    digitalWrite(l1, led1);
    digitalWrite(l2, led2);
    digitalWrite(l3, led3); //Write all the leds
    digitalWrite(l4, led4);
    digitalWrite(l5, led5);
    digitalWrite(l6, led6);
    int currPos = 0;
    boolean a = true; //While no button is pressed
    do
    {
        currPos = constrain(analogRead(potentiometer)/140, 0, 5);
        Game::servo.write(map(currPos, 0, 5.0, 20.0, 170.0));
        a = digitalRead(but1) && digitalRead(but2) && digitalRead(but3) && digitalRead(but4); //Set a equal to all the buttons so it will exit if any of them are pressed
    }while(a);

    int b = Game::waitForButtons(); //Get the button number that was pressed
    if(b != buttons+1 || currPos != positions) //If the button is incorrect or if the position is incorrect
        return false;
    return true;
}