/*
  GameRunner.cpp - Library for controlling all of the game functions.
*/

#include "GameRunner.h"
#include <iostream>
#include "Gui_top.h"
#include <time.h>
#include "EasyBMP.h"
#include "TaskManager.h"
#include <chrono>
#include <thread>
#include <functional>
using namespace std;

#ifdef _UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

int GameRunner::countdown = 0, GameRunner::W =0, GameRunner::H = 0, GameRunner::state = 0, GameRunner::playerNum = 1;
TaskManager GameRunner::taskManager;
NumberButton GameRunner::digits[9];
SerialPort GameRunner::arduino = SerialPort((char*) SerialPort::getPortName().c_str());

void timer_start(std::function<void(void)> func, unsigned int interval)
{
    std::thread([func, interval]() { //Make a separate thread for the timer
        while (true)
        {
            func();
            chrono::system_clock::time_point stamp = std::chrono::system_clock::now() + chrono::milliseconds(interval);
            std::this_thread::sleep_until(stamp);
        }
    }).detach();
}

void updateTimer() {
    if (GameRunner::countdown != 0) {
        GameRunner::countdown--;
        if(GameRunner::state == 1)
            updateScreen(0, 3*GameRunner::H/4, GameRunner::W, GameRunner::H);
        else if(GameRunner::state >= 2 && GameRunner::state <= 6) {
            updateScreen(0, GameRunner::H - GameRunner::H / 8 + GameRunner::H / 100, 7 * GameRunner::W / 8,
                         GameRunner::H);
        }
    }
    else if(GameRunner::countdown == 0)
    {
        if(GameRunner::state == 1) {
            long num = 0;
            for(int i = 0; i < 9; i++){
                num+= GameRunner::digits[i].num;
                num*=10;
            }
            num/=10;
            cout<<num<<endl;
            GameRunner::taskManager = TaskManager(num, GameRunner::digits[0].num, GameRunner::playerNum,
                                                  GameRunner::W, GameRunner::H - GameRunner::H / 8);
            if(true) { //For testing
                string g = "";
                for (int i = 0; i < 5; i++) {
                    g += to_string(TaskManager::taskOrder[i]+1);
                }
                GameRunner::arduino.send(g + "$"); //Send the task order to the arduino
                cout<<g<<endl;
                cout<<GameRunner::arduino.waitForRead()<<endl;
                for (int i = 0; i < 5; i++) {
                    g = "";
                    if(TaskManager::isBoth(i) || !TaskManager::isTaskGiver(i) || TaskManager::taskOrder[i] == 3 || TaskManager::taskOrder[i] == 6) {
                        if (TaskManager::taskOrder[i] == 0 || TaskManager::taskOrder[i] == 3 || TaskManager::taskOrder[i] == 6) {
                            for (int j = 0; j < TaskManager::randomVariables[i].size(); j++)
                                g += to_string(TaskManager::randomVariables[i][j]); //Just sending the random variables generated earlier
                        } else if (TaskManager::taskOrder[i] == 1) {
                            for (int j = 0; j < 8; j++)
                                g += to_string(TaskManager::randomVariables[i][j]); //Adding the first 8 variables which represent servo positions and button positions
                            g += to_string(TaskManager::randomVariables[i][TaskManager::randomVariables[i].size() - 2]); //Last two variables are the correct servo pos and button
                            g += to_string(TaskManager::randomVariables[i][TaskManager::randomVariables[i].size() - 1]);
                        } else if (TaskManager::taskOrder[i] == 4) {
                            for (int j = 0; j < 6; j++)
                                g += to_string(TaskManager::randomVariables[i][j]);
                        } else if (TaskManager::taskOrder[i] == 5) {
                            for (int j = 0; j < 6; j++)
                                g += to_string(TaskManager::randomVariables[i][j]);
                            for (int j = 0; j < 6; j++)
                                g += to_string(TaskManager::randomVariables[i][TaskManager::randomVariables[i][j]]);
                        }
                        else if(TaskManager::taskOrder[i] == 2)
                        {
                            string correctNum = "";
                            for(int j = 0; j < TaskManager::randomVariables[i].size(); j++)
                            {
                                if(TaskManager::randomVariables[i][j] >= 10)
                                {
                                    char c = TaskManager::randomVariables[i][j]+59;
                                    correctNum += string(1,c);
                                }
                                else
                                {
                                    correctNum += to_string(TaskManager::randomVariables[i][j]);
                                }
                            }
                            g+= correctNum;
                        }
                    }
                    else
                        g += "*";
                    GameRunner::arduino.send(g + "$");
                    cout<<g<<endl;
                    cout<<GameRunner::arduino.waitForRead()<<endl;
                }
            }
            GameRunner::state = 2;
            GameRunner::countdown = 600;
            updateScreen();
        }
        else if(GameRunner::state >= 2)
        {
            MessageBoxA("You ran out of time!", "You lost!");
            exit(0);
        }
    }
}

GameRunner::GameRunner() {

    if(arduino.isConnected()) {
        std::cout << "Connected" << endl;
        string read = arduino.waitForRead();
        if(read.find("ready", 0) == -1)
        {
            MessageBoxA("Arduino not communicating properly. Please ensure you chose the correct COM port and restart the program", "Communication Error");
            exit(0);
        }
    }
    else {
        MessageBoxA("Arduino not found. Please plug in the Arduino and restart the program", "Error");
        exit(0);
    }

    timer_start(updateTimer, 1000);
    W = GetMaxX()/5*4;
    H = GetMaxY()/5*4;

    std::cout << "Done"<<endl;

    startButton = Button("Start", W/7, 5*H/7, 3*W/7, 6*H/7);
    nextButton = Button("Next", W-W/8, H-H/8, W-W/30, H-H/20);
    playerButton = NumberButton("Host", 4*W/7, 5*H/7, 6*W/7, 6*H/7, 1, 9);

    for(int i = 1; i < 9; i++)
        digits[i] = NumberButton(std::string("0"), i*W/9,H/4, i*W/9 + W/9,3*H/4);
    digits[0] = NumberButton(std::string("1"), 0,H/4, W/9,3*H/4, 1, 9);

}

void GameRunner::paint() {
    if(state == 0)
        startScreenPaint();
    else if(state == 1)
        randomNumScreen();
    else {
        taskManager.Paint(state - 2);
        SetTextColor(RED);
        if(countdown <= 60)
            DrawCenteredText(to_string(countdown), 0, H-H/8+H/100, W, H-H/20);
        else {
            DrawCenteredText(to_string(countdown / 60) + ":" + + (countdown % 60 < 10 ? "0" : "") + to_string(countdown % 60), 0, H - H / 8 + H / 100, W,
                             H - H / 20);
        }
        SetTextColor(BLACK);
        nextButton.Paint();
    }
}

void GameRunner::randomNumScreen()
{
    SetColor(BLACK);
    SetFillColor(BLACK);
    FilledRectangle(0,0,W,H);
    gotoxy(0, H/6);
    if(host)
        rectangleText("Change first digit to number of players, then make sure everyone enters your number in!", 0, 0, W,  H/4);
    else
        rectangleText("Enter the hosts number correctly, and wait for the game to begin!", 0, 0, W,  H/4);
    for(int i = 0; i<9; i++)
        digits[i].Paint();

    rectangleText("Game Starting in: " + to_string(countdown), 0, 3*H/4, W, H);

}

void GameRunner::startScreenPaint()
{
    srand(time(NULL));
    SetColor(BLACK);
    SetFillColor(BLACK);
    FilledRectangle(0,0,W, H);
    SetColor(WHITE);
    for(int i = 0; i < 200; i++)
    {
        SetPixel(rand()%GetMaxX(), rand()%GetMaxY());
    }

    BMP logo;
    logo.ReadFromFile(std::string(workingdir() + std::string("logo (1).bmp")).c_str());
    Rescale(logo, 'W', GetMaxX()/5*3);
    int cx = W/2, cy = H/2;
    for(int i = 0; i < logo.TellWidth(); i++)
        for(int j = 0; j < logo.TellHeight(); j++) {
            int r = logo.GetPixel(i,j).Red, g = logo.GetPixel(i,j).Green, b = logo.GetPixel(i,j).Blue;
            SetColor(WHITE);
            if(r <= 50 && g <= 50 && b <= 50)
                SetPixel(cx - logo.TellWidth()/2 + i, cy - logo.TellHeight()/2 + j - H/8);
        }

    startButton.Paint();
    playerButton.Paint();
}

void GameRunner::mouseEvent(int x, int y) {
    if(state == 0) {
        if(startButton.I$$$$(x,y)) {
            playerNum = playerButton.increment(-1,-1);
            state++;
            long a = time(NULL) + 30;
            for(int i = 8; i >= 1; i--)
            {
                digits[i].num = a%10;
                digits[i].MyText = to_string(a%10);
                a /= 10;
            }

            long start = time(NULL)/10000000;
            for(int i = 1; i < 9; i++)
            {
                start += digits[i].num;
                if(i!=8)
                    start *= 10;
            }
            countdown = start - time(NULL);
        }
        if(playerButton.I$$$$(x,y))
        {
            if(playerButton.increment(x,y) == 1)
            {
                host = true;
                playerButton.MyText = "Host";
            }
            else
            {
                host = false;
                playerButton.MyText = "Player: " + to_string(playerButton.increment(-1,-1));
            }
        }
    }
    else if(state == 1) {
        if(!host) {
            for (int i = 0; i < 9; i++) {
                if (digits[i].num != digits[i].increment(x,y)) {
                    long start = time(NULL) / 10000000;
                    for (int i = 1; i < 9; i++) {
                        start += digits[i].num;
                        if (i != 8)
                            start *= 10;
                    }
                    countdown = start - time(NULL);
                    break;
                }
            }
        }
        else {
            digits[0].increment(x, y);
        }
    }
    else
    {
        taskManager.mouseClick(x,y,state-2);
        if(nextButton.I$$$$(x,y)) {
            if (taskManager.taskOrder[state - 2] == 2) {
                if (taskManager.verify())
                    state++;
                else
                    MessageBoxA("You entered the wrong number. Try again", "Incorrect Number");
            } else
                state++;
        }
    }

    if(state == 7) {
        MessageBoxA("You won!", "Winner!");
        exit(0);
    }
}

std::string GameRunner::workingdir()
{
    char buf[256];
    GetCurrentDirectoryA(256, buf);
    return std::string(buf) + '\\';
}


void GameRunner::rectangleText(string txt, int MyX1,int MyY1, int MyX2,int MyY2)
{
    SetColor(BLACK);
    gotoxy((MyX1+MyX2)/2, (MyY2-MyY1)/3.5/1.333+(MyY1+MyY2)/2);
    SetTextFont("Times New Roman");
    SetTextSize((MyX2-MyX1)/1.333/txt.length()*3);
    DrawCenteredText(txt);
}




