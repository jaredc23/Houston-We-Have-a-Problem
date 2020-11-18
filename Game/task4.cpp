/*
  task4.cpp - Library for task #4.
*/

#include "Arduino.h"
#include "task4.h"
#include "Game.h"


task4::task4() {}

task4::task4(int& echo, int& trig, int& r1, int& g1, int& b1, int& but) //Initializes the task with the necessary components
{
    uEcho = echo;
    uTrig = trig;
    r = r1;
    g = g1;
    b = b1;
    button = but;
}

boolean task4::start(int distance)  //This method starts the actual task using the information provided as the correct answer to the task
{

    long count = 3000; //Timer for a correct number
    long stamp = millis();
    distance = map(distance, 0, 9, 1, 50); //Change the distance from a single digit to an actual distance
    while(millis()-stamp <= count)
    {
        int a = getDistanceSensor(); //Getting the distance
        if(a <= distance - 25 || a >= distance + 25) { //If it is not in the distance (with wiggle room)
            stamp = millis();
            digitalWrite(b, LOW); //Turn the red led on and reset timer
            digitalWrite(r, HIGH);
        }
        else {
            digitalWrite(b, HIGH);
            digitalWrite(r, LOW); //turn the blue led on
        }
    }
    Game::ringBuzzer(200);//Ring the buzzer to indicate it was correct
    return true;
}

int task4::getDistanceSensor() //Get the distance sensor reading, helper function
{
    long duration;
    digitalWrite(uTrig, LOW);
    delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(uTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(uTrig, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(uEcho, HIGH);
// Calculating the distance
    return duration*0.034/2;
}