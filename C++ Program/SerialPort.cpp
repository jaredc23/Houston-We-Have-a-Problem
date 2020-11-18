#include "SerialPort.h"
#include <iostream>
#include <tchar.h>
#include <windows.h>

SerialPort::SerialPort(char *portName)
{
    this->connected = false;

    this->handler = CreateFileA(static_cast<LPCSTR>(portName),
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);
    if (this->handler == INVALID_HANDLE_VALUE){
        if (GetLastError() == ERROR_FILE_NOT_FOUND){
            printf("ERROR: Handle was not attached. Reason: %s not available\n", portName);
        }
    else
        {
            printf("ERROR!!!\n");
        }
    }
    else {
        DCB dcbSerialParameters = {0};

        if (!GetCommState(this->handler, &dcbSerialParameters)) {
            printf("failed to get current serial parameters");
        }
        else {
            dcbSerialParameters.BaudRate = CBR_115200;
            dcbSerialParameters.ByteSize = 8;
            dcbSerialParameters.StopBits = ONESTOPBIT;
            dcbSerialParameters.Parity = NOPARITY;
            dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(handler, &dcbSerialParameters))
            {
                printf("ALERT: could not set Serial port parameters\n");
            }
            else {
                this->connected = true;
                PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }
}

SerialPort::~SerialPort()
{
    if (this->connected){
        this->connected = false;
        CloseHandle(this->handler);
    }
}

int SerialPort::readSerialPort(char *buffer, unsigned int buf_size)
{
    DWORD bytesRead;
    unsigned int toRead = 0;

    ClearCommError(this->handler, &this->errors, &this->status);

    if (this->status.cbInQue > 0){
        if (this->status.cbInQue > buf_size){
            toRead = buf_size;
        }
        else toRead = this->status.cbInQue;
    }

    if (ReadFile(this->handler, buffer, toRead, &bytesRead, NULL)) return bytesRead;

    return 0;
}

std::string SerialPort::read()
{
    char buffer[MAX_DATA_LENGTH];
    int buf_size = MAX_DATA_LENGTH;
    DWORD bytesRead;
    unsigned int toRead = 0;

    ClearCommError(this->handler, &this->errors, &this->status);

    if (this->status.cbInQue > 0){
        if (this->status.cbInQue > buf_size){
            toRead = buf_size;
        }
        else toRead = this->status.cbInQue;
    }

    if (ReadFile(this->handler, buffer, toRead, &bytesRead, NULL)) return std::string(buffer);

    return NULL;
}

std::string SerialPort::readNumbers()
{
    char buffer[MAX_DATA_LENGTH];
    int buf_size = MAX_DATA_LENGTH;
    DWORD bytesRead;
    unsigned int toRead = 0;

    ClearCommError(this->handler, &this->errors, &this->status);

    if (this->status.cbInQue > 0){
        if (this->status.cbInQue > buf_size){
            toRead = buf_size;
        }
        else toRead = this->status.cbInQue;
    }

    if (ReadFile(this->handler, buffer, toRead, &bytesRead, NULL))
    {
        char toReturn[MAX_DATA_LENGTH];
        int index = 0;
        for(int i = 0; i < MAX_DATA_LENGTH; i++)
            if((buffer[i] < 58 && buffer[i] > 47) || buffer[i] == 36 || buffer[i] == 37)
            {
                toReturn[index] = buffer[i];
                index++;
            }
        //return std::string(buffer);
        return std::string(toReturn);
    }

    return NULL;
}

bool SerialPort::writeSerialPort(char *buffer, unsigned int buf_size)
{
    DWORD bytesSend;

    if (!WriteFile(this->handler, (void*) buffer, buf_size, &bytesSend, 0)){
        ClearCommError(this->handler, &this->errors, &this->status);
        return false;
    }
    else return true;
}

bool SerialPort::send(std::string text)
{
    char *charArray = new char[text.size() + 1];
    copy(text.begin(), text.end(), charArray);
    charArray[text.size()] = '\n';

    return writeSerialPort(charArray, MAX_DATA_LENGTH);
}

bool SerialPort::isConnected()
{
    return this->connected;
}

std::string SerialPort::readUntil(std::string s)
{
    std::string command = "";
    do
    {
        command = readNumbers();
    }while(command.compare("") == 0 || command.compare("\n") == 0 || command.find("%") == -1);

    while(command.find(s.c_str()) == -1){
        command += readNumbers();
    }
    return command.substr(command.find("%") + 1);
}

std::string SerialPort::waitForRead()
{
    std::string command = "";
    do
    {
        command = read();
    }while(command.compare("") == 0 || command.compare("\n") == 0 || command.find("%") == -1);
    return command.substr(command.find("%") + 1);
}


void SerialPort::DetectComPorts(std::vector< tstring >& ports, size_t upperLimit)
{
    for(size_t i=1; i<=upperLimit; i++)
    {
        TCHAR strPort[32] = {0};
        _stprintf(strPort, _T("COM%d"), i); //  \\.\

        DWORD dwSize = 0;
        LPCOMMCONFIG lpCC = (LPCOMMCONFIG) new BYTE[1];
        BOOL ret = GetDefaultCommConfig(strPort, lpCC, &dwSize);
        delete [] lpCC;

        lpCC = (LPCOMMCONFIG) new BYTE[dwSize];
        ret = GetDefaultCommConfig(strPort, lpCC, &dwSize);
        delete [] lpCC;

        if(ret) ports.push_back(strPort);
    }
}

#include <stdio.h>
std::string SerialPort::getPortName() {
    std::vector< tstring > ports;
    DetectComPorts(ports);
    for(std::vector< tstring >::const_iterator it = ports.begin(); it != ports.end(); ++it)
    {
        if (MessageBox(NULL, (char*)((std::string("We detected a control unit on ") + std::string(it->c_str()) + std::string(", is this correct?")).c_str()), "Confirm Port Selection",
                       MB_YESNO | MB_ICONQUESTION) == IDYES)
            return ((std::string(R"(\\.\)") + std::string(it->c_str())).c_str());
    }
    return "Serial ports were";
}
