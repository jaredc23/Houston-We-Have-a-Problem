/*
 * Houston, we have a problem
 *
 * This is the main file for the C++ program to go along with the Arduino program and circuit
 *
*/

/* PC 2 Arduino */

#include<iostream>
using namespace std;
#include<string>
#include"SerialPort.h"
#include "GameRunner.h"
#include "Gui_top.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>


class GuiClass //Defining GuiClass instead of main because GUIS are periodic and not a one time thing like main
{
public:
    GuiClass();
    void GuiMouseClick(int x, int y);
    void GuiPaint();
    string Title();
private:
    GameRunner g; //This is the game
};

GuiClass::GuiClass()
{

}

string GuiClass::Title() //This sets the title
{
    return("Houston, We Have a Problem");
}

void GuiClass::GuiMouseClick(int x, int y) //what do do when the mouse is clicked
{
    g.mouseEvent(x,y); //Triggers a mouse event
}

void GuiClass::GuiPaint() //When the screen is repainted
{
    g.paint(); //Call the paint function
}

#include "Gui_bot.h"
