/*
  task5.cpp - Library for task 5.
*/

#include "Arduino.h"
#include "task5.h"
#include "Game.h"


task5::task5() {}

task5::task5(int echo, int trig, int but, int leds[]) //Initializes the task with the necessary components
{
    uEcho = echo;
    uTrig = trig;
    button = but;
    led1 = leds[0];
    led2 = leds[1];
    led3 = leds[2];
    led4 = leds[3];
    led5 = leds[4];
    led6 = leds[5];
}

boolean task5::start(int l1, int l2, int l3, int l4, int l5, int l6)  //This method starts the actual task using the information provided as the correct answer to the task
{
    int avg[100]; //Makes an average so that the readings are cleaner
    for(int i = 0; i< 100; i++)
        avg[i] = 0;
    for(int i = 0; i < 6; i++)
    {
        int d = 0;
        boolean but = true; //Create variables for each button
        while(but == true)
        {
            d = getDistanceSensor(); //Gets the distance sensor reading
            d = constrain(d, 1, 30); //Constraining it makes it easier to manipulate
            for(int i = 1; i < 100; i++)
                avg[i-1] = avg[i];
            avg[99] = d;
            int sum = 0; //The next few lines is calculating the average reading
            for(int i = 0; i<100;i++)
                sum += avg[i];
            d = sum/100.0; //Set d to the avg reading
            d = map(d, 1, 30, 0,6); //Get the correct led from the distance sensor reading

            boolean leds[6] = {0,0,0,0,0,0};
            leds[d] = true; //Set the correct LED on
            setLeds(leds);
            but = digitalRead(button); //Read button to see if it was pressed
        }

        while(digitalRead(button) == false); //Wait until button is unpressed to get rid of false triggers
        delay(100);
        if(i == 0) { //Check to make sure the correct light is on and if so ring the buzzer, if not return false
            if (d == l1)
                Game::ringBuzzer(200);
            else
                return false;
        }
        else if(i == 1) { //Check to make sure the correct light is on and if so ring the buzzer, if not return false
            if (d == l2)
                Game::ringBuzzer(200);
            else
                return false;
        }
        else if(i == 2) {//Check to make sure the correct light is on and if so ring the buzzer, if not return false
            if (d == l3)
                Game::ringBuzzer(200);
            else
                return false;
        }
        else if(i == 3) {//Check to make sure the correct light is on and if so ring the buzzer, if not return false
            if (d == l4)
                Game::ringBuzzer(200);
            else
                return false;
        }
        else if(i == 4) {//Check to make sure the correct light is on and if so ring the buzzer, if not return false
            if (d == l5)
                Game::ringBuzzer(200);
            else
                return false;
        }
        else if(i == 5) {//Check to make sure the correct light is on and if so ring the buzzer, if not return false
            if (d == l6)
                Game::ringBuzzer(200);
            else
                return false;
        }

    }
    return true;
}

void task5::setLeds(boolean leds[]) //Helper function to turn on and off the leds without having to write digitalWrite a lot
{
    digitalWrite(led1, leds[0]);
    digitalWrite(led2, leds[1]);
    digitalWrite(led3, leds[2]);
    digitalWrite(led4, leds[3]);
    digitalWrite(led5, leds[4]);
    digitalWrite(led6, leds[5]);
}

int task5::getDistanceSensor() //Helper function to read the distance sensor
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