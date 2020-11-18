#ifndef SERIALPORT_H
#define SERIALPORT_H

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#ifdef _UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

class SerialPort
{
private:
    HANDLE handler;
    bool connected;
    COMSTAT status;
    DWORD errors;
public:
    SerialPort(char *portName);
    ~SerialPort();

    int readSerialPort(char *buffer, unsigned int buf_size);
    bool writeSerialPort(char *buffer, unsigned int buf_size);
    bool send(std::string text);
    std::string read();
    bool isConnected();
    std::string waitForRead();
    std::string readUntil(std::string s);
    std::string readNumbers();
    static void DetectComPorts(std::vector< tstring >& ports, size_t upperLimit = 128);
    static std::string getPortName();
};

#endif // SERIALPORT_H

