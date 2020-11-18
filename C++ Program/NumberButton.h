//
// Created by Jared on 10/21/2020.
//

#ifndef MAIN_CPP_NUMBERBUTTON_H
#define MAIN_CPP_NUMBERBUTTON_H

#include <iostream>
using namespace std;

class NumberButton {
public:
    NumberButton();
    NumberButton(string Text, int X1, int Y1, int X2, int Y2);
    NumberButton(string Text, int X1, int Y1, int X2, int Y2, int minValue, int maxValue);
    void Paint();
    bool I$$$$(int X, int y);
    int increment(int x, int y);
    string MyText;
    int num = 0;

private:
    int MyX1, MyY1, MyX2, MyY2,  min = 0, max = 9;

};

class Button {
public:
    Button();
    Button(string Text, int X1, int Y1, int X2, int Y2);
    void Paint();
    bool I$$$$(int X, int y);
    string MyText;

private:
    int MyX1, MyY1, MyX2, MyY2;

};

#endif
