/*
  task6.cpp - Library for task 6.
*/

#include "Arduino.h"
#include "task6.h"
#include "Game.h"

task6::task6() {}

task6::task6(int *leds, int b1) //Initializes the task with the necessary components
{
    l1 = leds[0];
    l2 = leds[1];
    l3 = leds[2];
    l4 = leds[3];
    l5 = leds[4];
    l6 = leds[5];
    but1 = b1;

}

boolean task6::start(int s1, int s2, int s3, int s4, int s5, int s6, int led1, int led2, int led3, int led4, int led5, int led6) //This method starts the actual task using the information provided as the correct answer to the task
{
    int s[] = {s1,s2,s3,s4,s5,s6}; //Make it easier to iterate with these arrays
    int leds[] = {led1, led2, led3, led4, led5, led6};
    for(int i = 0; i < 6; i++)
    {
        Game::servo.write(map(s[i], 0, 5, 20, 160)); //Map the servo position to tha angle
        int count = 0;
        while(digitalRead(but1))
        {
            boolean l[] = {0,0,0,0,0,0};
            l[count] = 1;
            setLeds(l);
            if(count+1 != 6) //Set the on led to the next one in line, unless it is the last led then set to the first
                count++;
            else
                count = 0;
            long stamp = millis();
            while(digitalRead(but1) && millis()-stamp < 300) //This is a delay that does not block so the player can press the button whenever they want
            {
                //Do nothing because we are waiting for the leds to change. Cannot use delay because that blocks the program
            }
        }
        while(!digitalRead(but1)); //While the button is not pressed because it is inverted

        if(count == 0) //Fixing count because it is one ahead for some reason
            count = 5;
        else
            count--;
        if(count != leds[i]) //Making sure the correct led was stopped
            return false;
        else
            Game::ringBuzzer(200); //Making a noise if it was right
    }
    return true;
}

void task6::setLeds(boolean leds[]) //Helper function which just sets all the leds. Avoids tediousness of writing out digitalWrite
{
    digitalWrite(l1, leds[0]);
    digitalWrite(l2, leds[1]);
    digitalWrite(l3, leds[2]);
    digitalWrite(l4, leds[3]);
    digitalWrite(l5, leds[4]);
    digitalWrite(l6, leds[5]);
}