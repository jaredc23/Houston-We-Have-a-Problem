/*
  task7.cpp - Library for task 7.
*/

#include "Arduino.h"
#include "task7.h"
#include "Game.h"

task7::task7() {}

task7::task7(int& buzz, int& pot, int rled, int bled, int gled) //Initializes the task with the necessary components
{
    buzzer = buzz;
    potentiometer = pot;
    r = rled;
    b = bled;
    g = gled;
}

boolean task7::start(int tone1, int tone2, int tone3) //This method starts the actual task using the information provided as the correct answer to the task
{
    tone1 = map(tone1, 0, 9.0, 123.0, 989.0); //Since we are only sending single digits this converts those single digits to the desired frequency range
    tone2 = map(tone2, 0, 9.0, 123.0, 989.0);
    tone3 = map(tone3, 0, 9.0, 123.0, 989.0);
    int tones[] = {tone1, tone2, tone3}; //Making it easier to loop with

    for(int i = 0; i < 3; i++)
    {
        long count = 3000; //3 seconds for it to be right
        long stamp = millis();
        Serial.println(millis()-stamp);
        int avg[100]; //This average array allows wiggle room for readings with noise
        for(int i = 0; i < 100; i++)
            avg[i] = 0; //setting everything to zero initially
        while(millis()-stamp <= count)
        {
            int a = map(analogRead(potentiometer), 0, 1023, 123.0, 989.0); //Read the potentiometer and set it to a frequency
            tone(buzzer, a); //Play that frequency
            for(int i = 1; i < 100; i++)
                avg[i-1] = avg[i]; //Move everything in the array forward
            avg[99] = a; //Set the last element to the last frequency
            long sum = 0;
            for(int i = 0; i < 100; i++)
                sum += avg[i];
            a = sum/100; //Calculate the average of this array to get a better reading without noise
            if(a < tones[i] - 50 || a > tones[i] + 50) //If the tone doesnt match the tone with 50hz wiggle room
            {
                Game::servo.write(0);//Turn the servo to the zero pos
                stamp = millis(); //Set the timer to zero
            }
            else {
                Game::servo.write(90); //Set to the middle
            }
        }
        Game::ringBuzzer(500); //Since this is repeated we set the buzzer to indicate to move on
    }
    return true; //return true since this task can't be failed.
}