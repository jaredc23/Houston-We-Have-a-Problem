
How to play the game (Software)
---

This is a full runthrough of how to fully upload/run all the correct code.
The four things you (and everyone else playing the game) needs to do is listed below.

**NOTE: I CANNOT GUARANTEE GAME IS NOT SUPPORTED ON MAC DUE TO THE USAGE OF WINDOWS FUNCTIONS**

## Download
* **On the top right of the screen, click the "Code" button, then download as zip.**
* **Then extract to a convenient place, such as your Desktop.**
## Arduino Code pt 1.

This part will be for the code that you need to install in your directories before being able to upload code.

* First, copy the folder called "Game" into the Arduino libraries folder.
  * This folder is located in **C:\\Users\\Name\\Documents\\Arduino\\libraries\\**
## Arduino Code pt. 2

This part is the easiest, just open test.ino, inside of the folder **Arduino/test**, and upload test.ino. If you get errors, go back to Arduino pt1 and make sure everything is in the correct folder.

## C++ Program

This part will go over how to properly run the C++ Program.

* Open CLion
* Click File>Open
* Select the folder called "C++ Program" (**not** any individual files) and open it.
* Once the folder opens in CLion, double click the file CMakeLists.txt
* Plug in your Arduino (with the code uploaded) before the next steps.
* Click the run button on the top right (or Run>'Serial_test').
* This build process should take a few seconds and ***there should be a few warnings, just ignore them.***
* After a few more seconds, it should pop up a window asking if the Arduino is correct, just click yes.

## Troubleshooting
If there are any errors, make sure that all the files are in the correct location.
* If the arduino program will not upload: Make sure that the directory is structured like **C:\\Users\\Name\\Documents\\Arduino\\libraries\\Game**, and inside the game folder is all the task files (You should see task1.h, task1.cpp, task2.h, task2.cpp, and so on, including some other files).
* If the C++ program is not running (The play button is greyed out): Make sure you open the entire folder and that CLion knows that it is apart of a project.
* If the C++ program quits after running with an error: Make sure you are not on a mac, I have not tested it with a mac and due to some of the dependencies, I suspect it may not work.
