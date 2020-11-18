//
// Created by Jared on 11/1/2020.
//

#include <vector>
#include <iostream>
#include "NumberButton.h"
//#include "Gui_top.h"
using namespace std;

#ifndef MAIN_CPP_TASKMANAGER_H
#define MAIN_CPP_TASKMANAGER_H


class TaskManager {
public:
    TaskManager();
    TaskManager(long seed, int NumPlayers, int playerNum, int W, int H);
    void Paint(int taskNumber);
    void mouseClick(int x, int y, int taskNumber);
    bool verify();
    vector<int> getNonRepeatingVector(int min, int max);
    vector<int> getNonRepeatingVector(int num, int min, int max);
    vector<int> getNonRepeatingVector(vector<int> nums);
    vector<int> concat(vector<int> a, vector<int>b);
    static vector<vector<int>> randomVariables;
    static vector<vector<int>> players;
    static vector<int> taskOrder;
    static bool isBoth(int taskNum);
    static bool isTaskGiver(int taskNumber);
private:
    static int w, h, pNum;
    long correctNum;
    NumberButton digits[5];
    int getTaskGiver(int taskNumber);
    int getTaskReceiver(int taskNumber);
    void DrawTable(string title, int x1, int y1, int x2, int y2, vector<string> left, vector<string> right);
};


#endif //MAIN_CPP_TASKMANAGER_H
