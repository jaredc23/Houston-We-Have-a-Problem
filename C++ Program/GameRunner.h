/*
  test.h - Library for test.
*/
#ifndef GameRunner_h
#define GameRunner_h

#include "SerialPort.h"
#include "NumberButton.h"
#include "TaskManager.h"
#include <iostream>
#include <functional>
using namespace std;

class GameRunner {
public:
    GameRunner();
    void connectArduino();
    void paint();
    void startScreenPaint();
    void randomNumScreen();
    void mouseEvent(int x, int y);
    static std::string workingdir();
    static void rectangleText(string txt, int MyX1,int MyY1, int MyX2,int MyY2);
    static int countdown;
    static int W, H, state, playerNum;
    static TaskManager taskManager;
    static NumberButton digits[9];
    static SerialPort arduino;
private:
    Button startButton, nextButton;
    NumberButton playerButton;
    boolean host = true;
};
#endif