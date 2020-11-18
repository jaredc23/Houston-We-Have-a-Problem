/*
  task3.cpp - Library for task #.
*/

#include "Arduino.h"
#include "task3.h"
#include "Game.h"

task3::task3() {}

task3::task3(int leds[]) //Initializes the task with the necessary components
{
    l1 = leds[0];
    l2 = leds[1];
    l3 = leds[2];
    l4 = leds[3];
    l5 = leds[4];
    l6 = leds[5];
}

boolean task3::start(int values[]) //This method starts the actual task using the information provided as the correct answer to the task
{
    int length = 2000; //length of time between each movement, 2 secs.
    for(int i = 0; i < 5; i++)
    {
        int a = values[i]; //Get the value
        if(a == 0) //If its less than 6, turn on corresponding led, then delay and turn it off
        {
            digitalWrite(l1, HIGH);
            delay(length);
            digitalWrite(l1, LOW);
        }
        else if(a == 1) //If its less than 6, turn on corresponding led, then delay and turn it off
        {
            digitalWrite(l2, HIGH);
            delay(length);
            digitalWrite(l2, LOW);
        }
        else if(a == 2)//If its less than 6, turn on corresponding led, then delay and turn it off
        {
            digitalWrite(l3, HIGH);
            delay(length);
            digitalWrite(l3, LOW);
        }
        else if(a == 3)//If its less than 6, turn on corresponding led, then delay and turn it off
        {
            digitalWrite(l4, HIGH);
            delay(length);
            digitalWrite(l4, LOW);
        }
        else if(a == 4)//If its less than 6, turn on corresponding led, then delay and turn it off
        {
            digitalWrite(l5, HIGH);
            delay(length);
            digitalWrite(l5, LOW);
        }
        else if(a == 5)//If its less than 6, turn on corresponding led, then delay and turn it off
        {
            digitalWrite(l6, HIGH);
            delay(length);
            digitalWrite(l6, LOW);
        }
        else //If it is a servo movement, change the servo to the correct position
        {
            Game::servo.write(map(a, 6.0, 11.0, 10.0, 170.0));
            delay(length);
        }

        Game::ringBuzzer(200); //Ring the buzzer to indicate when each movement is done

    }

    return true; //Always return true, because the checking is done inside the actual task
}