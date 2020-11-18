/*
  Game.cpp - Library for controlling gameplay.
*/

#include "Arduino.h" //Including nessesary libraries
#include "Game.h"

//Defining all of the static variables
Servo Game::servo;
int Game::rp = 0;
int Game::bp = 0;
int Game::gp = 0;
int Game::bpin = 0;
int Game::leds[6], Game::rgbled[3], Game::buttons[4], Game::uping, Game::uecho, Game::buzzer, Game::pot;




Game::Game(int *ledpins, int *rgbpins, int *buttonpins, int ultraPing, int ultraEcho,
           int buzzerPin, int potentiometer) //Initializes all the leds, buttons, temp sensor, pins for ultrasonic sensors, servo, and buzzer
{
    for(int i = 0; i < 6; i++) //Setting all the pins for LEDS and setting them to outputs
    {
        leds[i] = ledpins[i];
    }

    for(int i = 0; i < 4; i++) //Setting all the pins for the buttons and setting them to inputs
    {
        buttons[i] = buttonpins[i];
    }

    for(int i = 0; i < 3; i++) //Setting all the button
    {
        rgbled[i] = rgbpins[i];
    }

    //Setting all the variables
    buzzer = buzzerPin;
    pot = potentiometer;
    uping = ultraPing;
    uecho = ultraEcho;

    //Creating each tasks
    t1 = task1(buttons[0], buttons[1], buttons[2], buttons[3]);
    t2 = task2(buttons[0], buttons[1], buttons[2], buttons[3], pot, leds);
    t3 = task3(leds);
    t4 = task4(ultraEcho, ultraPing, rgbled[0], rgbled[1], rgbled[2], buttons[0]);
    t5 = task5(ultraEcho, ultraPing, buttons[0], leds);
    t6 = task6(leds, buttons[0]);
    t7 = task7(buzzer, pot, rgbled[0],rgbled[1],rgbled[2]);

    bpin = buzzerPin; //Setting the RGB leds and the buzzer pin
    rp = rgbpins[0];
    gp = rgbpins[1];
    bp = rgbpins[2];


}

void Game::setup() //This method sets up all of the pins
{
    for(int i = 0; i < 6; i++) //Setting all the pins for LEDS and setting them to outputs
    {
        pinMode(leds[i], OUTPUT);
    }

    for(int i = 0; i < 4; i++) //Setting all the pins for the buttons and setting them to inputs
    {
        pinMode(buttons[i], INPUT_PULLUP); //Buttons are used as input pullup.
    }

    for(int i = 0; i < 3; i++) //Setting all the button
    {
        pinMode(rgbled[i], OUTPUT);
    }

    pinMode(buzzer, OUTPUT); //Setting the pinmode for the buzzer and the ultrasonic sensor
    pinMode(uping, OUTPUT);
    pinMode(uecho, INPUT);


    pinMode(A1, INPUT_PULLUP);

}

int Game::waitForButtons() { //This function waits for one button to be pressed and returns which button it was (1-4)
   boolean a = true, b = true, c = true, d = true; //Create variables for each button
   while(a && b && c && d) //Loop while none of the buttons are pressed (wired so that when the button is pressed it is pulled LOW)
   {
       a = digitalRead(buttons[0]);
       b = digitalRead(buttons[1]);
       c = digitalRead(buttons[2]);
       d = digitalRead(buttons[3]);
   }

   int bNum = 4; //Set the button number and use an if statement to see which button was pressed.
   if(!a)
       bNum = 1;
   else if(!b)
       bNum = 2;
   else if(!c)
       bNum = 3;

   while(!digitalRead(buttons[bNum - 1])); //Wait for that button to be unpressed so it does not trigger multiple times

   delay(100); //Wait 100ms to allow for debouncing the button

   return bNum; //return the button number
}

void Game::waitForSerial(long timeout)
{
    long stamp = millis();
    while(!Serial.available()) {
        if (millis() - stamp > timeout) {
            Serial.println("%The Arduino is not properly communicating with the computer");
            digitalWrite(13, HIGH);
            while (true);
        }
    }
}

void Game::waitForSerialNoTimeout()
{
    while(!Serial.available()) {
        //do nothing
    }
}

void Game::startSerial() { //Starts the serial communication with the c++ program.
    Serial.begin(115200); //Fast baud rate is less delays for players
    Serial.setTimeout(100); //Set timeout low so that Serial functions dont take a long time (optional and honestly negligible)
    Serial.println("%%ready"); //Send ready so the computer knows the arduino is ready, the %sign makes it easier to parse
    digitalWrite(13, HIGH); //For testing
    waitForSerialNoTimeout(); //Wait for the computer to respond to the ready command
    digitalWrite(13, LOW);//For testing
    String data[6]; //All of the data, where the first represents the task order, and the rest are for the tasks. Strings will be parsed later
    for(int i = 0; i <= 5; i++) {
        String t = Serial.readStringUntil("$"); //Read data from computer, stop on the $ to avoid getting characters that are not useful
        String j;
        for(int k = 0; k < t.length()-1; k++) //This is to extract all the numbers from the string
        {
            if(t.charAt(k) == 36) //If it is the dollar sign stop reading
                break;
            if((t.charAt(k) < 58 && t.charAt(k) > 47) || t.charAt(k) == 36 || t.charAt(k) == 37 || t.charAt(k) == 42) //If it is a number, *, $, or % add it to the string
                j += t.substring(k, k+1);
            else if(t.charAt(k) >= 65 && t.charAt(k) < 72) { //If it is a letter add it
                j += t.substring(k, k + 1);
            }
        }
        data[i] = j;
        digitalWrite(13, HIGH); //For debugging purposes
        Serial.println("%" + j); //Print the data back to the computer to verify, will be removed later
        if(i != 5) //Unless it is the last piece of info wait for the next reading
            waitForSerialNoTimeout();
    }

    for(int i =0; i < 5; i++)
    {
        taskOrder[i] = data[0].substring(i, i+1).toInt(); //Setting the order of the tasks
    }
    for(int i = 0; i< 5; i++)
    {
        for(int j = 0; j < numRand[taskOrder[i]]; j++) //Loop through each task
        {
            int k = i+1; //Making it easier since the first thing in data[] is the task order
            String c = data[k].substring(j, j+1);
            if(c.charAt(0) == 42) { //If it's a * we do not want the player using the arduino (task giver) so this will allow it to skip
                variables[i][0] = -1;
                break;
            }
            else{
                if(taskOrder[i] == 0 || taskOrder[i] == 3 || taskOrder[i] == 4 || taskOrder[i] == 5 || taskOrder[i] == 6) //If the tasks are any of these just copy over the info because it is all the same
                    variables[i][j] = c.toInt();
                else if(taskOrder[i] == 2) //If the task is 2, since it is written in HEX we need to convert it back to decimal and then to servo positions by messing with the ascii value
                {
                    if((int)c.charAt(0) >= 65) {
                        variables[i][j] = c.charAt(0) - 59;
                    }
                    else
                        variables[i][j] = c.toInt(); //If its not a letter just copy over
                }
                else if(taskOrder[i] == 1) //If task 2
                {
                    int f[4] = {0,2,1,3}, s[4] = {5,2,4,3}; //Creating reference arrays to line up with the chart in the C++ program
                    int leds[6] = {0,0,0,0,0,0}; //Initializing the led array
                    int first = data[k].substring(8,9).toInt(); //Getting the correct Servo and button and setting it to the correct variables in the array
                    int second = data[k].substring(9,10).toInt();
                    variables[i][6] = data[k].substring(first, first+1).toInt();
                    variables[i][7] = data[k].substring(second+4, second+5).toInt();
                    leds[f[first]] = 1; //Translating the C++ colors to the arduino color and setting that led to true
                    leds[s[second]] = 1;
                    for(int t = 0; t < 6; t++)
                        variables[i][t] = leds[t]; //Setting the variables to the corresponding leds
                    j = numRand[taskOrder[i]]; //Leaving the loop so that this only happens once since everything happens already.
                }
            }
        }
    }
}

void Game::Test() //Test function will be removed later
{
    Game::servo.write(map(analogRead(pot), 0, 1023, 20 ,160));
    Serial.println(waitForButtons());
    for(int i = 0; i < 6; i++)
        digitalWrite(leds[i], !digitalRead(leds[i]));
    Game::correct();
}

void Game::loop() //Loop function that will eventually go through each task and handle all of the game actions
{
    for(int i = 0; i < 5; i++) //Loop through each task
    {
        boolean b = false;
        int taskNumber = taskOrder[i];
        if(variables[i][0] != -1) { //If the task requires the arduino
            do {
                if (taskNumber == 0) { //Each one of these is just calling the start function for each task
                    b = t1.start(variables[i][0], variables[i][1], variables[i][2], variables[i][3], variables[i][4],
                                 variables[i][5]);
                } else if (taskNumber == 1) {
                    b = t2.start(variables[i][0], variables[i][1], variables[i][2], variables[i][3], variables[i][4],
                                 variables[i][5], variables[i][6], variables[i][7]);
                } else if (taskNumber == 2) {
                    int y[6] = {variables[i][0], variables[i][1], variables[i][2], variables[i][3], variables[i][4], variables[i][5]};
                    b = t3.start(y);
                    if(waitForButtons() == 4)
                        b = false;
                } else if (taskNumber == 3) { //This task needs to be called 3 separate times so that is why it repeats
                    for (int k = 0; k < 3; k++) {
                        b = t4.start(variables[i][k]);
                        if (b == false)
                            k = 5;
                    }
                } else if (taskNumber == 4) {
                    b = t5.start(variables[i][0], variables[i][1], variables[i][2], variables[i][3], variables[i][4],
                                 variables[i][5]);
                } else if (taskNumber == 5) {
                    b = t6.start(variables[i][0], variables[i][1], variables[i][2], variables[i][3], variables[i][4],
                                 variables[i][5], variables[i][6], variables[i][7], variables[i][8], variables[i][9],
                                 variables[i][10], variables[i][11]);
                } else if (taskNumber == 6) {
                    b = t7.start(variables[i][0], variables[i][1], variables[i][2]);
                }

                if(!b) //If the task was done incorrectly play the wrong sound
                    wrong();
            } while (b == false); //Loop until the task is correct
        }
        else { //If the player is a task giver for this round
            while(waitForButtons() != 1); //Wait for button one to be pressed so that the arduino is at the same pace.
            correct();
        }
        correct(); //Indicate that it is correct and move on to the next task
        for(int i = 0; i < 6; i++)
            digitalWrite(leds[i], LOW);
    }
}

void Game::ringBuzzer(int duration) //Plays a buzzer tone to indicate a correct answer but not the end of a task
{
    tone(bpin, 466); //Play tone
    delay(duration); //wait duration
    noTone(bpin); //stop tone
}

void Game::correct() { //This is a function for indicating correct, static so that every task can use it and has a cohesive feel
    digitalWrite(rp, LOW);
    digitalWrite(bp, LOW);
    digitalWrite(gp, HIGH); //Turning on the green LED
    tone(bpin, 466); //Playing a tone
    delay(100);
    digitalWrite(rp, LOW);
    digitalWrite(bp, LOW);
    digitalWrite(gp, LOW); //Turning off the LEDs and tone
    noTone(bpin);
    delay(50);
    digitalWrite(rp, LOW);
    digitalWrite(bp, LOW);
    digitalWrite(gp, HIGH); //Different tone and green led turn on
    tone(bpin, 988);
    delay(100);
    noTone(bpin);
    delay(500);
    digitalWrite(rp, LOW); //Turn everything off.
    digitalWrite(bp, LOW);
    digitalWrite(gp, LOW);
}

void Game::wrong() {  //This is a function for indicating correct, static so that every task can use it and has a cohesive feel
    digitalWrite(rp, HIGH);
    digitalWrite(bp, LOW);
    digitalWrite(gp, LOW); //Turn red led on and play tone
    tone(bpin, 123);
    delay(100);
    digitalWrite(rp, LOW);
    digitalWrite(bp, LOW);
    digitalWrite(gp, LOW);//Turn everything off
    noTone(bpin);
    delay(50);
    digitalWrite(rp, HIGH);
    digitalWrite(bp, LOW);//Turn the red LED back on and play a different tone
    digitalWrite(gp, LOW);
    tone(bpin, 123);
    delay(100);
    noTone(bpin);
    delay(500);
    digitalWrite(rp, LOW); //Turn everything off
    digitalWrite(bp, LOW);
    digitalWrite(gp, LOW);
}