cmake_minimum_required(VERSION 3.17)
project(Serial_Test)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_HEADERS
        SerialPort.h
        GameRunner.h
        Gui_bot.h
        Gui_top.h
        EasyBMP.h
        EasyBMP_BMP.h
        EasyBMP_DataStructures.h
        EasyBMP_VariousBMPutilities.h
        NumberButton.h
        TaskManager.h)
set(PROJECT_SOURCES
        main.cpp
        SerialPort.cpp
        GameRunner.cpp
        EasyBMP.cpp
        NumberButton.cpp
        TaskManager.cpp)

add_executable(Serial_Test ${PROJECT_SOURCES} ${PROJECT_HEADERS})
