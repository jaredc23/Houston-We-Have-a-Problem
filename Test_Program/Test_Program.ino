#include <Game.h> //Including the game library. Put libraries in a folder called Game in User/Documents/Arduino/libraries
//Red Green Blue yellow green red //This is the correct order of all of the leds.
const int leds[6] = {2,4,5,6,11,12}; //Setting the 6 led pins
const int rgb[3] = {7,8,A5}; //Setting the rgb led pins
const int buttons[4] = {A1,A2,A3,A4}; //Setting all of the button pins
Game game(leds, rgb, buttons, 10, 13, 9, 0); //Creating a game object
Servo s;//Making the servo

void setup() {
  s.attach(3);//Attaching the servo pin to the servo
  Game::servo = s; //Setting the servo so all the tasks can use it
  game.setup(); //Sets up all of the pins
  //game.startSerial(); //Starts serial with the computer and gets the data
}

void loop() {
  game.Test();
  //game.loop();//This is what calls all of the functions
  //while(true);//Stop once the game is finished. Arduino auto resets when connecting to serial so the arduino can stay plugged in
}
