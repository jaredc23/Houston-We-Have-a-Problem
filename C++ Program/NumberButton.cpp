//
// Created by Jared on 10/21/2020.
//

#include "NumberButton.h"
#include <iostream>
#include "Gui_top.h"
using namespace std;

NumberButton::NumberButton()
{

}

NumberButton::NumberButton(string Text, int X1, int Y1, int X2, int Y2)
        :MyText(Text), MyX1(X1), MyY1(Y1), MyX2(X2), MyY2(Y2)
{
}

NumberButton::NumberButton(string Text, int X1, int Y1, int X2, int Y2, int minValue, int maxValue)
        :MyText(Text), MyX1(X1), MyY1(Y1), MyX2(X2), MyY2(Y2), min(minValue), max(maxValue), num(minValue)
{
}

//------------------------------------------------------------------------
void NumberButton::Paint()
{
    SetColor(BLACK);
    SetFillColor(212,208,200);
    FilledRectangle(MyX1, MyY1, MyX2, MyY2);
    gotoxy((MyX1+MyX2)/2, (MyY2-MyY1)/3.5/1.333+(MyY1+MyY2)/2);
    SetTextFont("Times New Roman");
    SetTextSize((MyY2-MyY1)/1.333);
    DrawText(MyText, MyX1, MyY1, MyX2, MyY2);
}

//------------------------------------------------------------------------
bool NumberButton:: I$$$$(int x, int y)
{
    return(x>=MyX1 && x<=MyX2 && y>=MyY1 && y<=MyY2);
}

int NumberButton::increment(int x, int y)
{
    if(I$$$$(x, y))
    {
        if(num !=max)
            num++;
        else
            num = min;

        MyText = to_string(num);
    }

    return num;
}



//--------Button Class------------------------------------------------------------
Button::Button()
{

}

Button::Button(string Text, int X1, int Y1, int X2, int Y2)
        :MyText(Text), MyX1(X1), MyY1(Y1), MyX2(X2), MyY2(Y2)
{
}

//------------------------------------------------------------------------
void Button::Paint()
{
    SetColor(BLACK);
    SetFillColor(212,208,200);
    FilledRectangle(MyX1, MyY1, MyX2, MyY2);
    gotoxy((MyX1+MyX2)/2, (MyY2-MyY1)/3.5/1.333+(MyY1+MyY2)/2);
    SetTextFont("Times New Roman");
    SetTextSize((MyY2-MyY1)/1.333);
    SetFillColor(BLUE);
    DrawCenteredText(MyText);
}

//------------------------------------------------------------------------
bool Button:: I$$$$(int x, int y)
{
    return(x>=MyX1 && x<=MyX2 && y>=MyY1 && y<=MyY2);
}