//
// Created by Jared on 11/1/2020.
//

#include "TaskManager.h"
#include "GameRunner.h"
#include "Gui_top.h"
#include <tgmath.h>


vector<vector<int>> TaskManager::randomVariables;
vector<vector<int>> TaskManager::players;
vector<int> TaskManager::taskOrder;
int TaskManager::w,TaskManager::h,TaskManager::pNum;

TaskManager::TaskManager() {
}



int rnd(int low, int high)
{
    return rand()%high + low;
}

int find(vector<int> a, int b)
{
    for(int i = 0; i < a.size(); i++)
    {
        if(b == a.at(i))
            return i;
    }
    return -1;
}

bool TaskManager::isBoth(int taskNumber)
{
    return (find(players[taskNumber], pNum)%2 == 0 && players[taskNumber][find(players[taskNumber], pNum) + 1] == pNum);
}

bool TaskManager::isTaskGiver(int taskNumber)
{
    return find(players[taskNumber], pNum)%2 == 0;
}

int TaskManager::getTaskGiver(int taskNumber)
{
    return players[taskNumber][find(players[taskNumber], pNum) - 1];
}

int TaskManager::getTaskReceiver(int taskNumber) {
    return players[taskNumber][find(players[taskNumber], pNum) + 1];
}

void TaskManager::DrawTable(string title, int x1, int y1, int x2, int y2, vector<string> left, vector<string> right)
{
    for(int i = 0; i < left.size() + 1; i++)
    {
        if(i == 0)
        {
            DrawCenteredText(title, x1,y1,x2,y1+(y2-y1)/(left.size()+1));
        }
        else
        {
            DrawCenteredText(left[i-1], x1,y1+(y2-y1)/(left.size()+1)*i,x2/2,y1+(y2-y1)/(left.size()+1)*(i+1));
            DrawCenteredText(right[i-1], x2/2,y1+(y2-y1)/(left.size()+1)*i,x2,y1+(y2-y1)/(left.size()+1)*(i+1));
        }
        SetColor(BLACK);
        Line(x1,y1+(y2-y1)/(left.size()+1)*i, x2, y1+(y2-y1)/(left.size()+1)*i);
    }
    Line(x1,y2,x2,y2);
    Line((x2-x1)/2, y1 + (y2-y1)/(left.size()+1), (x2-x1)/2, y2);
}

void TaskManager::mouseClick(int x, int y, int taskNumber) {
    if(taskOrder[taskNumber] == 2)
    {
        if(isBoth(taskNumber)) {
            for(int i = 0; i < 5; i++)
                digits[i].increment(x,y);
        }
        else if(!isTaskGiver(taskNumber))
        {
            for(int i = 0; i < 5; i++)
                digits[i].increment(x,y);
        }
    }
}

void TaskManager::Paint(int taskNumber)
{
    int W = w, H = h/2;
    SetFillColor(BLACK);
    SetFillColor(227,223,215);
    FilledRectangle(0,0,W, (2*H)+h/8);
    if(taskOrder[taskNumber] == 0)
    {
        if(isBoth(taskNumber)){
            GameRunner::rectangleText("Press buttons in the order shown. After each new button is pressed, start over.",
                                      0, H / 4, W, 3 * H / 4);
            string temp = "";
            for (int i = 0; i < randomVariables[taskNumber].size(); i++)
                temp += to_string(randomVariables[taskNumber][i] + 1) +
                        (i != randomVariables[taskNumber].size() - 1 ? ":" : "");
            H = 2 * H;
            GameRunner::rectangleText(temp, 0, H / 4, W, 3 * H / 4);
        }
        else if(isTaskGiver(taskNumber))
        {
            GameRunner::rectangleText("Tell player " + to_string(getTaskReceiver(taskNumber)) + " to press the buttons in the order shown. After each new button is pressed, start over.",
                                      0, H / 4, W, 3 * H / 4);
            string temp = "";
            for (int i = 0; i < randomVariables[taskNumber].size(); i++)
                temp += to_string(randomVariables[taskNumber][i] + 1) +
                        (i != randomVariables[taskNumber].size() - 1 ? ":" : "");
            H = 2 * H;
            GameRunner::rectangleText(temp, 0, H / 4, W, 3 * H / 4);
        }
        else
        {
            DrawCenteredText(" Ask player number " + to_string(getTaskGiver(taskNumber)) + " for the directions ", 0,h/4,w,h/2);
            DrawCenteredText(" For each new button press, start the sequence from the beginning ", 0,h/2,w,3*h/4);
        }
    }
    else if(taskOrder[taskNumber] == 1)
    {
        if(isBoth(taskNumber)){
            vector<string> left;
            vector<string> right;
            left.push_back("Red:");
            left.push_back("Blue:");
            left.push_back("Green:");
            left.push_back("Yellow:");
            for(int i = 0; i < 4; i++) {
                char num[1] = {(char)(randomVariables[taskNumber][i] + 65)};
                string b = "";
                b.append(1, num[0]);
                right.push_back("Turn Servo to: " + b);
            }
            vector<string> t;
            DrawTable("What is the color of the first LED?", 0, 0, w, H, left, right);
            for(int i = 4; i < 8; i++) {
                t.push_back("Press button: " + to_string(randomVariables[taskNumber][i]+1));
            }
            DrawTable("What is the color of the last LED?", 0, H, w, h-h/25, left, t);
        }
        else if(isTaskGiver(taskNumber))
        {
            vector<string> left;
            vector<string> right;
            left.push_back("Red:");
            left.push_back("Blue:");
            left.push_back("Green:");
            left.push_back("Yellow:");
            for(int i = 0; i < 4; i++) {
                char num[1] = {(char)(randomVariables[taskNumber][i] + 65)};
                string b = "";
                b.append(1, num[0]);
                right.push_back("Turn Servo to: " + b);
            }
            vector<string> t;
            DrawTable("What is the color of the first LED?", 0, 0, w, H, left, right);
            for(int i = 4; i < 8; i++) {
                t.push_back("Press button: " + to_string(randomVariables[taskNumber][i] + 1));
            }
            DrawTable("What is the color of the last LED?", 0, H, w, h-h/25, left, t);
        }
        else
        {
            DrawCenteredText(" Ask player number " + to_string(getTaskGiver(taskNumber)) + " for the directions ", 0,h/4,w,h/2);
            DrawCenteredText("   Based on the LED order, use the knob to change the servo position and press a certain button   ", 0,h/2,w,3*h/4);
        }
    }
    else if(taskOrder[taskNumber] == 2)
    {
        correctNum = 0;
        for(int i = 0; i < randomVariables[taskNumber].size(); i++)
        {
            if(randomVariables[taskNumber][i] == 1 || randomVariables[taskNumber][i] == 4)
                correctNum += 2;
            else if(randomVariables[taskNumber][i] == 2)
                correctNum += 1;
            else if(randomVariables[taskNumber][i] == 3)
                correctNum += 3;
            else if(randomVariables[taskNumber][i] != 0 && randomVariables[taskNumber][i] != 5)
            {
                correctNum += randomVariables[taskNumber][i]-2;
            }
            correctNum*=10;
        }
        correctNum/=10;
        cout<<endl;
        cout<<"Correct: "<<correctNum<<endl;
        if(isBoth(taskNumber)){
            vector<string> left;
            vector<string> right;
            left.push_back("Action:");
            left.push_back("LED: Red");
            left.push_back("LED: Blue");
            left.push_back("LED: Green");
            left.push_back("LED: Yellow");
            left.push_back("Servo: A");
            left.push_back("Servo: B");
            left.push_back("Servo: C");
            left.push_back("Servo: D");
            left.push_back("Servo: E");
            left.push_back("Servo: F");
            right.push_back("Number");
            for(int i = 0; i <= 9; i++) {
                right.push_back(to_string(i));
            }
            DrawTable("Watch the Arduino and enter in the corresponding number below. Press Button 1 to restart", 0, 0, w, H, left, right);
            for(int i = 0; i < 5; i++) {
                digits[i].Paint();
            }
        }
        else if(isTaskGiver(taskNumber))
        {
            correctNum = 0;
            for(int i= 0; i< 5 ;i++)
                digits[i].num = 0;
            vector<string> left;
            vector<string> right;
            left.push_back("Action:");
            left.push_back("LED: Red");
            left.push_back("LED: Blue");
            left.push_back("LED: Green");
            left.push_back("LED: Yellow:");
            left.push_back("Servo: A");
            left.push_back("Servo: B");
            left.push_back("Servo: C");
            left.push_back("Servo: D");
            left.push_back("Servo: E");
            left.push_back("Servo: F");
            right.push_back("Number");
            for(int i = 0; i <= 9; i++) {
                right.push_back(to_string(i));
            }
            DrawTable("   Tell player " + to_string(getTaskReceiver(taskNumber)) + " the corresponding numbers to enter into their computer   ", 0, 0, w, h, left, right);
        }
        else
        {
            DrawCenteredText(" Tell player number " + to_string(getTaskGiver(taskNumber)) + " what happens, and enter in the numbers ", 0,h/4,w,h/2);
            for(int i = 0; i < 5; i++) {
                digits[i].Paint();
            }
        }
    }
    else if(taskOrder[taskNumber] == 3)
    {
        SetFillColor(RED);
        FilledRectangle(0,0,w,h);
        DrawCenteredText(" SYSTEM ERROR ", 0,0,w,h/2);
        DrawCenteredText("   Use the ultrasonic sensor to turn the LED and keep it there for 3 seconds   ", 0,h/4,w,3*h/4);
        DrawCenteredText("                                    repeat this 3 times                                    ", 0,h/4,w,h);
    }
    else if(taskOrder[taskNumber] == 4) //For task 5
    {
        vector<string> characters;
        for(int i = 6; i < 12; i++)
        {
            char num[1] = {(char)(randomVariables[taskNumber][i])};
            string b = "";
            b.append(1, num[0]);
            characters.push_back(b);
        }
        if(isBoth(taskNumber)){
            vector<string> left;
            vector<string> right;
            for(int i = 12; i < 18; i ++)
            {
                left.push_back(characters[find(randomVariables[taskNumber], randomVariables[taskNumber][i]) - 6]);
            }
            for(int i = 12; i < 18; i++) {
                right.push_back("Turn on LED " + to_string(randomVariables[taskNumber][find(randomVariables[taskNumber], randomVariables[taskNumber][i]) - 6]+1));
            }
            string g;
            for(int i = 0; i < characters.size(); i++)
                g += characters[i];
            DrawTable("Your sequence: " + g, 0, 0, w, h, left, right);
        }
        else if(isTaskGiver(taskNumber))
        {
            vector<string> left;
            vector<string> right;
            for(int i = 12; i < 18; i ++)
            {
                left.push_back(characters[find(randomVariables[taskNumber], randomVariables[taskNumber][i]) - 6]);
            }
            for(int i = 12; i < 18; i++) {
                right.push_back("Turn on LED " + to_string(randomVariables[taskNumber][find(randomVariables[taskNumber], randomVariables[taskNumber][i]) - 6]+1));
            }
            DrawTable("    Player " + to_string(getTaskReceiver(taskNumber)) + " has a series of characters. Tell them the correct LEDs to turn on.    ", 0, 0, w, h, left, right);
        }
        else
        {
            string g;
            for(int i = 0; i < characters.size(); i++)
                g += characters[i];
            DrawCenteredText(" Ask player number " + to_string(getTaskGiver(taskNumber)) + " for the which LED to turn on ", 0,h/4,w,h/2);
            DrawCenteredText("   Based on this sequence: " + g +" tell the other player, in order, your sequence    ", 0,h/2,w,3*h/4);
        }
    }
    else if(taskOrder[taskNumber] == 5) //Task 6
    {
        vector<string> characters; //Create the vector of correct characters
        for(int i = 65; i <= 71; i++)
        {
            char num[1] = {(char)(i)};
            string b = "";
            b.append(1, num[0]);
            characters.push_back(b); //Add the characters
        }
        if(isBoth(taskNumber)){ //If both the task giver and reciever
            vector<string> left;
            vector<string> right;
            for(int i = 0; i < 6; i++)
            {
                char num[1] = {(char)(randomVariables[taskNumber][randomVariables[taskNumber][i]] + 65)};  //Add the corect character to the vector
                string b = "";
                b.append(1, num[0]);
                left.push_back(b);
            }
            for(int i = 0; i < 6; i++) {
                string led = to_string(randomVariables[taskNumber][randomVariables[taskNumber][randomVariables[taskNumber][i]]] + 1); //Add the correct led to the column vector
                right.push_back("  Stop LED number " + led + "  "); //Format it
            }
            DrawTable("      Stop the an LEDs with button 1 depending on the servo position      ", 0, 0, w, h, left, right); //Create a table with the info

        }
        else if(isTaskGiver(taskNumber))
        {
            vector<string> left;
            vector<string> right;
            for(int i = 0; i < 6; i++)
            {
                char num[1] = {(char)(randomVariables[taskNumber][randomVariables[taskNumber][i]] + 65)};
                string b = "";
                b.append(1, num[0]);
                left.push_back(b);
            }
            for(int i = 0; i < 6; i++) {
                string led = to_string(randomVariables[taskNumber][randomVariables[taskNumber][randomVariables[taskNumber][i]]] + 1);
                right.push_back("Stop LED  number " + led + "  ");
            }
            DrawTable("     Get the servo position from player " + to_string(getTaskReceiver(taskNumber)) + " and report back what they should do     ", 0, 0, w, h, left, right);
        }
        else
        {
            string g;
            for(int i = 0; i < characters.size(); i++)
                g += characters[i];
            DrawCenteredText(" Ask player number " + to_string(getTaskGiver(taskNumber)) + " for the which LED to turn on ", 0,h/4,w,h/2);
            DrawCenteredText("   Report to them your servo position, and use button 1 to stop the correct LED   ", 0,h/2,w,3*h/4);
        }
    }
    else if(taskOrder[taskNumber] == 6) //Task 7
    {
        SetFillColor(RED);
        FilledRectangle(0,0,w,h);
        DrawCenteredText(" Machinery Out of Tune  ", 0,0,w,h/2); //Draw text with instructions
        DrawCenteredText("   Turn the potentiometer to tune the frequency until the Servo is in the middle.    ", 0,h/4,w,3*h/4);
        DrawCenteredText("                                    Repeat this 3 times then click next.                                   ", 0,h/4,w,h);
    }
}

bool TaskManager::verify() //Verifies if the digits are the same number as the correct answer
{
    long num = 0;
    for(int i = 0; i < 5; i++){
        num+= digits[i].num;
        num*=10;
    }
    num/=10;
    return num == correctNum;
}


TaskManager::TaskManager(long seed, int numPlayers, int playerNum, int W, int H) { //Constructor to make the task manager object

    pNum = playerNum;
    w = W;
    h = H;

    if(pNum > numPlayers) //If the number was entered wrong
    {
        MessageBox("You selected a player number that is larger than the amount of players in the game. Please restart and make sure to change the first digit correctly", "Error");
        exit(0);
    }

    for(int i = 0; i < 5; i++)
        digits[i] = NumberButton(std::string("0"), i*W/5,H/2, i*W/5 + W/5,H);

    srand(seed);
    int numVariables[7] = {6, 10, 5, 3, 18, 12, 3}; //Makes it so it iterates a different amount of times each time
    for(int i = 0; i < 5; i++)
    {
        int taskNum = rnd(0,6);
        while(i > 0 && taskNum == taskOrder.at(taskOrder.size() - 1))
        {
            taskNum = rnd(0,6);
        }
        taskOrder.push_back(taskNum);
        vector<int> temp;
        for(int j = 0; j < numVariables[taskNum]; j++)
        {
            if(taskNum == 0)
            {
                temp.push_back(rnd(0,4));
            }
            else if(taskNum == 1)
            {
                vector<int> first = getNonRepeatingVector(4,0,5); //Which servo positions to turn to
                vector<int> second = getNonRepeatingVector(4,0,3); //Which buttons to press
                temp = concat(first, second);
                temp.push_back(rnd(0,4)); //Which Servo position is correct
                int a = rnd(0,4);
                while(temp.at(temp.size() - 1) == 1 && a == 3) //This is to avoid a yellow light for the first one and blue for the second which would break the game.
                {
                    a = rnd(0,4);
                }
                temp.push_back(a); //Which button number is correct
                j = numVariables[taskNum]; //End loop
            }
            else if(taskNum == 2)
            {
                temp.push_back(rnd(0,12)); //1-12 for thr 6 leds and the 6 servo position
            }
            else if(taskNum == 3)
            {
                temp.push_back(rnd(0,9)); //add a random variable for the distance
            }
            else if(taskNum == 4)
            {
                vector<int> first = getNonRepeatingVector(0,5);
                vector<int> second = getNonRepeatingVector(6, 65,90); //represents the letters
                temp = concat(first, second); //combine the two vectors
                temp = concat(temp, getNonRepeatingVector(second)); //Used for reordering the letters in the chart so it is not the same order
                j = numVariables[taskNum]; //End the loop
            }
            else if(taskNum == 5)
            {
                vector<int> first = getNonRepeatingVector(0,5); //Each one of these numbers is needed to properly playe each task and set up the program
                vector<int> second = getNonRepeatingVector(0, 5);//Each one of these numbers is needed to properly playe each task and set up the program
                temp = concat(second, first);
                j = numVariables[taskNum];
            }
            else if(taskNum == 6)
            {
                temp.push_back(rnd(0,9));//Each one of these numbers is needed to properly playe each task and set up the program
            }
        }
        randomVariables.push_back(temp); //Add the variables to the array
    }

    for(int i = 0; i < randomVariables.size(); i++) //Used for making all of the players order
    {
        vector<int> temp = getNonRepeatingVector(1, numPlayers); //Get the order in a nonrepeating way
        if(numPlayers%2 != 0)
        {
            temp.push_back(temp.at((temp.size()-1))); //If theres an odd number the player will be both the giver and reciever
        }
        players.push_back(temp); //Adding the players for each task
    }
}

vector<int> TaskManager::getNonRepeatingVector(int min, int max) //Gets a non repeating random vector (inclusive)
{
    vector<int> nums;
    for(int i = min; i <= max; i++)
    {
        nums.push_back(i); //Create the vector of numbers, in order
    }
    vector<int> toReturn;
    int y = nums.size();
    for(int i = 0; i < y; i++)
    {
        int a = rnd(0, nums.size());
        toReturn.push_back(nums.at(a)); //Pick a random element and add it to the new vector, erase it from the old vector, essentially shuffling
        nums.erase(nums.begin() + a);
    }
    return toReturn;
}

vector<int> TaskManager::getNonRepeatingVector(int num, int min, int max) //Gets a non repeating random vector only of a certain amount (must be <=) (inclusive)
{
    vector<int> nums;
    for(int i = min; i <= max; i++)
    {
        nums.push_back(i);  //Create a vector with all of the random numbers
    }
    vector<int> toReturn;

    for(int i = 0; i < num; i++)
    {
        int a = rnd(0, nums.size());
        toReturn.push_back(nums.at(a)); //Pick a random element and add it to the new vecor, erase it from the old vector
        nums.erase(nums.begin() + a);

    }
    return toReturn;
}

vector<int> TaskManager::getNonRepeatingVector(vector<int> nums)//Gets a non repeating random vector using a preexisting vector (inclusive)
{
    vector<int> toReturn;
    int b = nums.size();
    for(int i = 0; i < b; i++)
    {
        int a = rnd(0, nums.size());
        toReturn.push_back(nums.at(a));
        nums.erase(nums.begin() + a);
    }
    return toReturn;
}

vector<int> TaskManager::concat(vector<int> a, vector<int>b) { //adds two vectors and returns them as one
    vector<int> toReturn;
    for (int i = 0; i < a.size(); i++)
    {
        toReturn.push_back(a[i]);
    }
    for(int i = 0; i < b.size(); i++)
    {
        toReturn.push_back(b[i]);
    }
    return toReturn;
}