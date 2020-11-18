/*
  test.h - Library for test.
*/
#ifndef GameRunner_h
#define GameRunner_h //Make sure gamerunner is not redefined

#include "SerialPort.h"
#include "NumberButton.h"
#include "TaskManager.h"
#include <iostream>
#include <functional>
using namespace std;

class GameRunner {
public:
    GameRunner();
    void connectArduino(); //Connects arduino to the computer
    void paint();//Calls the paint function which decided what to draw
    void startScreenPaint(); //Paints the start screen
    void randomNumScreen(); //Paints the screen with all of the random number
    void mouseEvent(int x, int y); //When the mouse is clicked, this handles it
    static std::string workingdir(); //Gets the directory so the bitmap loads correctly
    static void rectangleText(string txt, int MyX1,int MyY1, int MyX2,int MyY2); //Draws text in rectangle
    static int countdown;         //Necessary variables for gameplay
    static int W, H, state, playerNum;
    static TaskManager taskManager;
    static NumberButton digits[9];
    static SerialPort arduino; //This is the arduino
private:
    Button startButton, nextButton; //other variables
    NumberButton playerButton;
    boolean host = true;
};
#endif