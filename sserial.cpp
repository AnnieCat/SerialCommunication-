#include <stdio.h>
#include <tchar.h>
#include "sserial.h"
#include <string>
#include <iostream>
#include <windows.h>

serial::serial(char *portName,int baudRate,unsigned char stopBits,unsigned char parity,int byteSize)
{
	std::string complexPortName("\\\\.\\");
	complexPortName+=portName;

    //Try to connect to the given port throuh CreateFile
    hserial = CreateFileA(complexPortName.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);

    //Check if the connection was successfull
    if(hserial==INVALID_HANDLE_VALUE)
    {
		printf("CreateFileA(...) returned error code %d\n", GetLastError());

        //If not success full display an Error
        if(GetLastError()==ERROR_FILE_NOT_FOUND) throw std::runtime_error("serial: could not bind to COM port");
		else throw std::runtime_error("serial: unknown serial error");
    }

    //If connected we try to set the comm parameters
    DCB dcbserialParams = {0};

    //Try to get the current
    if (!GetCommState(this->hserial, &dcbserialParams)) throw std::runtime_error("serial: failed to get current serial parameters!");

    //Define serial connection parameters for the device
    dcbserialParams.BaudRate=baudRate;
    dcbserialParams.ByteSize=byteSize;
    dcbserialParams.StopBits=stopBits;
    dcbserialParams.Parity=parity;

    //Set the parameters and check for their proper application
    if(!SetCommState(hserial, &dcbserialParams)) throw std::runtime_error("serial: Could not set serial Port parameters");
}

serial::~serial()
{
    CloseHandle(this->hserial);
}

int serial::available()
{
	DWORD errors;
	COMSTAT comstat;
	ClearCommError(hserial, &errors, &comstat);
	return comstat.cbInQue;
}

void serial::read(void * data, size_t size)
{
	char * dataBytes = reinterpret_cast<char *>(data);
	while (size > 0)
	{
		DWORD received;
		if (!ReadFile(hserial, dataBytes, size, &received, NULL)) throw std::runtime_error("serial::read(...) - ReadFile(...) failed");
		dataBytes += received;
		size -= received;
    }
}

void serial::write(const void * data, size_t size)
{
	DWORD sent;
	if (!WriteFile(hserial, data, size, &sent, 0)) throw std::runtime_error("serial::write(...) - WriteFile(...) failed");
}