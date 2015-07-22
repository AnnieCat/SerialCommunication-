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

uint16_t bufferR[256];
uint16_t bufferG[256];
uint16_t bufferB[256];

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
	/*Image image("sampleImage.jpg");
	int r = image.GetPixel(10, 10, 0);
	int g = image.GetPixel(10, 10, 1);
	int b = image.GetPixel(10, 10, 2);*/

	serial Serial("COM3", CBR_115200);


	Image image("sampleImage.jpg");
	/*int r = image.GetPixel(200, 10, 0);
	int g = image.GetPixel(200, 10, 1);
	int b = image.GetPixel(200, 10, 2);*/


	for (int y = 0; y < 1; ++y)
	{
		for (int x = 0; x < 1; ++x)
		{
			for (int c = 0; c < 3; ++c)
			{
				Serial.write(image.GetPixel(x * 20, y * 20, c));
			}
		}
	}

	uint8_t response = Serial.read();
	cout << "We received a response of " << (int)response << endl;

/*while(true)
	{
		Image image("sampleImage.jpg");
		/*int r = image.GetPixel(200, 10, 0);
		int g = image.GetPixel(200, 10, 1);
		int b = image.GetPixel(200, 10, 2);
		
		
		for (int i = 0; i < 2; i++){

			bufferR[i] = image.GetPixel(i * 20 + 10, 0, 0);
			bufferG[i] = image.GetPixel(i * 20 + 10, 0, 1);
			bufferG[i] = image.GetPixel(i * 20 + 10, 0, 2);

			Serial.write(bufferR[i]);
			Serial.write(bufferG[i]);
			Serial.write(bufferB[i]);

			cout << "R array element " << i << "is " << bufferR[i] << endl;
		}

		
		//cin >> r >> g >> b;
		//cout << "your values are " << r << " " << g << " " << b << endl;

		//Serial.write(r);
		//Serial.write(g);
		//Serial.write(b);

		//int avail = Serial.available();
		//cout << "(There are " << avail << " bytes ready right now)" << endl;
		uint8_t response = Serial.read();
		//cout << "We received a response of " << (int)response << endl;
	}*/
}


