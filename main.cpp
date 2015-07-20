/**
 --------------------------------------------------------------------------------------------
 This is a sample file, which shows how to read data from a serial port using both the
 blocking read() function and the asynchronous callback() function, as well as how to write
 data to the serial port using the write() function.
 This program simultaneously reads from and writes to the serial port.
 --------------------------------------------------------------------------------------------
 **/
#include "sserial.h"
#include <cstdint>	// For uint8_t
#include <iostream> // For cin, cout, endl

using namespace std;



int main()
{
	serial Serial("COM3", CBR_115200);
	while(true)
	{
		int r, g, b;
		cin >> r >> g >> b;
		cout << "your values are " << r << " " << g << " " << b << endl;

		Serial.write(r);
		Serial.write(g);
		Serial.write(b);

		int avail = Serial.available();
		cout << "(There are " << avail << " bytes ready right now)" << endl;
		uint8_t response = Serial.read();
		cout << "We received a response of " << (int)response << endl;
	}
}


