// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6


  Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

//float g = 0;
//float b = 0;
//uint16_t myColor = matrix.Color(r,g,b);


void setup() {
  matrix.begin();
  matrix.setBrightness(10);
  Serial.begin(115200);
  
}

void loop()
{
  if(Serial.available() > 0)
  {  
    matrix.fillScreen(0);
    matrix.setCursor(0,0);
    for (int y = 0; y < 8; ++y)
    {
      for (int x = 0; x < 32; ++x)
      {
        uint8_t r = Serial.read();
        uint8_t g = Serial.read();
        uint8_t b = Serial.read();
        matrix.drawPixel(x, y, matrix.Color(r,g,b));     
      }
    }
    matrix.show();  
      
    Serial.write(45);
  }
  
  //matrix.fillScreen(0);
  //matrix.setCursor(0,0);
  //matrix.drawPixel(0, 0, matrix.Color(r,g,b));
  //matrix.show();  
 }
