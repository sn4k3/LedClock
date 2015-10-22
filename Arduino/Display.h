// Display.h

#ifndef _DISPLAY_h
#define _DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define DISPLAY_MAX_TEXT_SIZE2 27
#define DISPLAY_MAX_TEXT_SIZE3 17
#define DISPLAY_MAX_TEXT_SIZE5 10

#define DISPLAY_HOURS_COLOR ILI9341_GREEN
#define DISPLAY_TEMPERATURE_COLOR ILI9341_WHITE

//#include <LiquidCrystal_I2C.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define CHAR_CLOCK 0
#define CHAR_TEMPERATURE 1
#define CHAR_HUMIDITY 2

class DisplayClass
{
 protected:
	 byte current_day;
	 byte current_hours[3];
	 float current_temperature;
	 float current_humidity;
	 bool radio_need_update;

 public:
	void init();
	byte alignCenterPadding(byte length, byte textSize);
	void render();

	// Define radio to be updated and rendered in the next frame
	void invalidate_radio();
};

extern DisplayClass Display;
extern Adafruit_ILI9341 tft;

#endif

