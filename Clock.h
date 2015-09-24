// Clock.h

#ifndef _CLOCK_h
#define _CLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Config.h"


#define MINUTES 60
#define HOURS 12
#define HOUR_TO_INDEX(hour) MINUTES + hour

#define NUM_LEDS 72

enum ClockStyle : byte
{
	ClockStyle_DEFAULT = 0, // Light up all LED to the current time
	ClockStyle_CURRENT,     // Light up only current time LED
	ClockStyle_NONE			// Don't light up

};


class ClockLED
{
 protected:
	 byte current_seconds_index;

 public:
	void init();
	void loop();


	void fadeLED(byte led, byte animationDelay = 20, bool fadeOut = true);
	void fill(byte fromLED, byte toLED, uint32_t color);
	void animateFill(byte fromLED, byte toLED, uint32_t color, unsigned short delayTime = 20);
	void blackLEDs();

	void colorWipe(uint32_t c, uint8_t wait);
	void rainbow(uint8_t wait);
	void rainbowCycle(uint8_t wait);
	void theaterChase(uint32_t c, uint8_t wait);
	void theaterChaseRainbow(uint8_t wait);
	uint32_t Wheel(byte WheelPos);

	void setBrightnessFromPhotoresistor();
	void setBrightness(byte value);

	void test1();
	void test2();
	void test3();
	void test4();
	void test5();
	void testAll();
};

extern ClockLED Clock;

#endif

