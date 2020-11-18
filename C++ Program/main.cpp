/* Zain Ul Mustafa 2017 */

//Rules:
/*
1. Check if connection with Arduino is made
2. If Arduino is connected then take input from user in a String
3. Make a char array of the size of string + 1
4. Copy the whole string into the char array
5. Add escape sequence \n because this represents the end of a line in Serial Comm port
6. Write the whole char array into the buffer (a buffer takes the info forward to the Serial Comm Port)
7. Read from the Arduino if data is received successfully or if the action is taken as per needed
*/

//Connect with me:
/*	Twitter: http://www.twitter.com/ZainsOfficial/
	Facebook: http://www.facebook.com/ZainsOfficial/
	Github: http://github.com/ZainUlMustafa/
*/

/* This software is allowed for any user to copy, modify, merge, and distribute in any of his/her project.
Complete repository for this project is available on github. If you find this project anywhere except github, it
is to be noted that it is not made by me and not distributed by me. 
Please follow this link to get to the original repository of github for this project
Github shortened link (no spam and no ads): http://bit.ly/2vGkinQ
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


class GuiClass
{
public:
    GuiClass();
    void GuiMouseClick(int x, int y);
    void GuiPaint();
    string Title();
private:
    GameRunner g;
};

GuiClass::GuiClass()
{

}

string GuiClass::Title()
{
    return("Houston, We Have a Problem");
}

void GuiClass::GuiMouseClick(int x, int y)
{
    g.mouseEvent(x,y);
}

void GuiClass::GuiPaint()
{
    g.paint();
}

#include "Gui_bot.h"
