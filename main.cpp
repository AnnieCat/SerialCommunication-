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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <memory>

using namespace std;

struct Image
{
	std::shared_ptr<uint8_t> pixels;
	int width, height, comp;

	Image(const char * filename)
	{
		auto p = stbi_load(filename, &width, &height, &comp, 0);
		pixels = std::shared_ptr<uint8_t>(p, stbi_image_free);
	}

	uint8_t GetPixel(int x, int y, int c) const
	{
		return pixels.get()[y*(width*comp) + x*comp + c];
	}
};

int main()
{
	int matrixWidth = 32, matrixHeight = 8;
	serial Serial("COM3", CBR_115200);

	Image image("testRainbow.jpg");


	for (int y = 0; y < 8; ++y)
	{
		for (int x = 0; x < 32; ++x)
		{
			for (int c = 0; c < 3; ++c)
			{
				Serial.write(image.GetPixel(x * 20, y * 20, c));
			}
		}
	}

	uint8_t response = Serial.read();
	cout << "We received a response of " << (int)response << endl;

}


