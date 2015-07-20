#ifndef SERIALCLASS_H_INCLUDED
#define SERIALCLASS_H_INCLUDED

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdint>

class serial
{
    HANDLE hserial;
public:
    serial(char *portName, int baudRate=CBR_9600, unsigned char stopBits=ONESTOPBIT, unsigned char parity=NOPARITY, int byteSize=8);
    ~serial();
        
	void read(void * data, size_t size);
	void write(const void * data, size_t size);

	int available();
	void write(uint8_t value) { write(&value, sizeof(value)); }
	uint8_t read() { uint8_t value; read(&value, sizeof(value)); return value; }
};

#endif // SERIALCLASS_H_INCLUDED
