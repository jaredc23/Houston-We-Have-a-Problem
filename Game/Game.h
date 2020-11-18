/*
  Game.h - Library for controlling gameplay.
*/

//Used to make sure no libraries are defined 2x, memory issue for arduino
#ifndef Game_h
#define Game_h

//Required libraries to include so code functions
#include "Arduino.h"
#include <Servo.h> //Servo library for the motor
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"      //All of the task libraries
#include "task5.h"
#include "task6.h"
#include "task7.h"

class Game
{
    public: //Public methods and variables
        //Setting the constructor to create a game object
        Game(int ledpins[], int rgbpins[], int buttonpins[], int ultraPing, int ultraEcho,
             int buzzerPin, int potentiometer);
        void startSerial();//Gets all the necessary info for the game from the computer. Initializes Serial Communication
        void waitForSerial(long timeout); //This waits for the serial monitor but it has a timeout and softlocks the arduino if it is reached
        void waitForSerialNoTimeout(); //This waits for serial monitor indefinitely
        void setup(); //This sets up all of the pins for all of the components
        void loop(); //This is the function that loops through the tasks and handles all of the tasks
        void Test(); //This is a test method that will be removed
        static void ringBuzzer(int duration); //Plays a note
        static void wrong(); //Calls with Game::wrong() or Game::correct() and triggers the buzzer and led to indicate
        static void correct();
        static int waitForButtons();//This is to get what button was pressed and avoid multiple presses
        //These are all the objects for the tasks, made public for testing purposes.
        task1 t1;
        task2 t2;
        task3 t3;
        task4 t4;
        task5 t5;
        task6 t6;
        task7 t7;
        //static LiquidCrystal lcd; //LCD is just here for testing, will be removed in the final version
        static Servo servo; //Static servo so that all tasks can access and control it.

    private: //Private methods and variables

        //Private Variables:
        //Setting the private variables for the pins for the leds, RGB LED, buttons, ultrasonic sensor, buzzer, and potentiometer
        static int leds[6], rgbled[3], buttons[4], uping, uecho, buzzer, pot;
        //Setting the private variable for servo. Creation of servo is done inside constructor
        int variables[5][12];
        int taskOrder[5];
        const int numRand[7] = {6, 8, 5, 3, 6, 12, 3};
        //This is to keep track of the number of players, may be removed later.
        //int numPlayers = 3;
        //These are the rgb led pins, which need to be static so correct() and wrong() can work
        static int bpin, rp, gp, bp;
        //Methods:

};

#endif