/**
 --------------------------------------------------------------------------------------------
 This is a sample file, which shows how to read data from a serial port using both the
 blocking read() function and the asynchronous callback() function, as well as how to write
 data to the serial port using the write() function.
 This program simultaneously reads from and writes to the serial port.
 --------------------------------------------------------------------------------------------
 **/
#include <stdio.h>
#include <tchar.h>
#include "sserial.h"
#include <string>
#include <iostream>
#include <windows.h>
#include "multithread.h"
#include "sserialException.h"
using namespace std;
void print(string& data,void* unused)
{
	cout<<data;
}

int main()
{
	
	//first, open the serial port
	//Adjust COM4 to whatever port your device is on
	serial port3("COM3", CBR_115200);

	//write some data from the console to the serial port
	//string input;
	//cin >> input;
	//port3.write(input);

	//Read some data and print it
	//program will pause until a whitespace character is read (just like cin)
	//cout<<port3.read();

	//Now, start reading data asynchronously (in a different thread).
	//This data will be printed with the print() function.
	//port3.callback(print);
	
	//now, start writing data from the console to the port forever
	while(true)
	{
		string input;
		cin >> input;
		port3.write(input);	
	}
}

