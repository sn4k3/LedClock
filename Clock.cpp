// 
// 
// 

#include "Clock.h"
#include "PhotoresistorSensor.h"
#include <Time.h>
#include <Adafruit_NeoPixel.h>

#define HOURS_COLOR Settings.clock_color[0]
#define MINUTES_COLOR Settings.clock_color[1]
#define SECONDS_COLOR Settings.clock_color[2]

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, 0, NEO_GRB + NEO_KHZ800);

void ClockLED::init()
{
#if defined (__AVR_ATtiny85__)
	if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif

	DEBUG_PRINTLN("CLOCK INIT");

	strip.begin();               // initialize strip
	strip.show();                // Update all LEDs (= turn OFF, since none of them have been set yet!)
	if(Settings.ledbrightness > 0)
	{
		strip.setBrightness(Settings.ledbrightness);
	}
	else
	{
		setBrightnessFromPhotoresistor();
	}

	DELAY_FUNC(10);

	current_seconds_index = 0;

	byte seconds = second();
	byte hours = hourFormat12();
	byte minutes = minute();
	if (hours == 12)
		hours = 0;

	animateFill(HOUR_TO_INDEX(0), HOUR_TO_INDEX(hours), HOURS_COLOR, 100);
	animateFill(0, minutes, MINUTES_COLOR, 50);

	/*uint32_t c = NEOCOLOR(255, 0, 0);  // define the variable c as RED (R,G,B)
	
	// First slide the led in one direction
	for (byte i = 0; i < NUM_LEDS; i++) {
		strip.setPixelColor(i, c);  // set LED 10 to the color in variable c (red)
		strip.show();
		strip.setPixelColor(i, 0);
		DELAY_FUNC(20);
	}
	// Now go in the other direction.  
	for (short i = NUM_LEDS - 1; i >= 0; i--) {
		strip.setPixelColor(i, c);  // set LED 10 to the color in variable c (red)
		strip.show();
		strip.setPixelColor(i, 0);
		DELAY_FUNC(20);
	}*/
}

void ClockLED::loop()
{
	byte seconds = second();

	if (current_seconds_index == seconds)
	{
		return;
	}

	byte hours = hourFormat12();
	byte minutes = minute();
	if (hours == 12)
		hours = 0;


	if (hours == 0 && minutes == 0 && (seconds == 0 || (seconds >= 0 && current_seconds_index >= 59)))
	{
		animateFill(HOUR_TO_INDEX(11), HOUR_TO_INDEX(0), 0, 50);
	}

	if (minutes == 0 && (seconds == 0 || (seconds >= 0 && current_seconds_index >= 59)))
	{
		animateFill(59, 0, 0);
	}

	if (current_seconds_index > minutes)
	{
		strip.setPixelColor(current_seconds_index, 0);
	}

	switch(Settings.clock_style[0])
	{
		case ClockStyle_CURRENT:
			fill(HOUR_TO_INDEX(0), HOUR_TO_INDEX(11), 0);
			strip.setPixelColor(HOUR_TO_INDEX(hours), HOURS_COLOR);
			break;
		case ClockStyle_DEFAULT:
		default:
			fill(HOUR_TO_INDEX(0), HOUR_TO_INDEX(hours), HOURS_COLOR);
			strip.setPixelColor(HOUR_TO_INDEX(hours), 255, 255, 0);
		break;
	}

	switch (Settings.clock_style[1])
	{
	case ClockStyle_CURRENT:
		fill(0, 59, 0);
		strip.setPixelColor(minutes, MINUTES_COLOR);
		break;
	case ClockStyle_DEFAULT:
	default:
		fill(0, minutes, MINUTES_COLOR);
		strip.setPixelColor(minutes, 255, 255, 0);
		break;
	}

	

	if (Settings.clock_style[2] != ClockStyle_NONE)
	{
		// Fix not shown seconds
		if ((seconds - current_seconds_index) > 1)
		{
			for (byte i = current_seconds_index; i <= seconds; i++)
			{
				uint16_t color = strip.getPixelColor(i);
				strip.setPixelColor(i, SECONDS_COLOR);
				strip.show();
				if (i == seconds)
					break;
				strip.setPixelColor(i, color);
				DELAY_FUNC(50);
			}
		}
		else
		{
			strip.setPixelColor(seconds, SECONDS_COLOR);
		}
	}

	current_seconds_index = seconds;

	strip.show();
}

void ClockLED::setBrightnessFromPhotoresistor()
{
	strip.setBrightness(Photoresistor.readValue());
}

void ClockLED::setBrightness(byte value)
{
	strip.setBrightness(value);
	strip.show();
}

void ClockLED::blackLEDs()
{
	strip.clear();
	strip.show();
}

void ClockLED::fadeLED(byte led, byte animationDelay, bool fadeOut)
{
	for (byte i = 255; i <= 0; i--)
	{
		DELAY_FUNC(animationDelay);
	}
}

void ClockLED::fill(byte fromLED, byte toLED, uint32_t color)
{
	if (fromLED <= toLED)
	{
		for (byte i = fromLED; i <= toLED; i++)
		{
			strip.setPixelColor(i, color);
		}
	}
	else
	{
		for (byte i = fromLED; i >= toLED; i--)
		{
			strip.setPixelColor(i, color);
			if (i == 0)
				break;
		}
	}
}

void ClockLED::animateFill(byte fromLED, byte toLED, uint32_t color, unsigned short delayTime)
{
	if (fromLED <= toLED)
	{
		for (byte i = fromLED; i <= toLED; i++)
		{
			strip.setPixelColor(i, color);
			strip.show();
			DELAY_FUNC(delayTime);
		}
	}
	else
	{
		for (byte i = fromLED; i >= toLED; i--)
		{
			strip.setPixelColor(i, color);
			strip.show();
			DELAY_FUNC(delayTime);
			if (i == 0)
				break;
		}
	}
}


// Fill the dots one after the other with a color
void ClockLED::colorWipe(uint32_t c, uint8_t wait) {
	for (uint16_t i = 0; i<strip.numPixels(); i++) {
		strip.setPixelColor(i, c);
		strip.show();
		DELAY_FUNC(wait);
	}
}

void ClockLED::rainbow(uint8_t wait) {
	uint16_t i, j;

	for (j = 0; j<256; j++) {
		for (i = 0; i<strip.numPixels(); i++) {
			strip.setPixelColor(i, Wheel((i + j) & 255));
		}
		strip.show();
		DELAY_FUNC(wait);
	}
}

// Slightly different, this makes the rainbow equally distributed throughout
void ClockLED::rainbowCycle(uint8_t wait) {
	uint16_t i, j;

	for (j = 0; j<256 * 5; j++) { // 5 cycles of all colors on wheel
		for (i = 0; i< strip.numPixels(); i++) {
			strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
		}
		strip.show();
		DELAY_FUNC(wait);
	}
}

//Theatre-style crawling lights.
void ClockLED::theaterChase(uint32_t c, uint8_t wait) {
	for (int j = 0; j<10; j++) {  //do 10 cycles of chasing
		for (int q = 0; q < 3; q++) {
			for (int i = 0; i < strip.numPixels(); i = i + 3) {
				strip.setPixelColor(i + q, c);    //turn every third pixel on
			}
			strip.show();

			DELAY_FUNC(wait);

			for (int i = 0; i < strip.numPixels(); i = i + 3) {
				strip.setPixelColor(i + q, 0);        //turn every third pixel off
			}
		}
	}
}

//Theatre-style crawling lights with rainbow effect
void ClockLED::theaterChaseRainbow(uint8_t wait) {
	for (int j = 0; j < 256; j++) {     // cycle all 256 colors in the wheel
		for (int q = 0; q < 3; q++) {
			for (int i = 0; i < strip.numPixels(); i = i + 3) {
				strip.setPixelColor(i + q, Wheel((i + j) % 255));    //turn every third pixel on
			}
			strip.show();

			DELAY_FUNC(wait);

			for (int i = 0; i < strip.numPixels(); i = i + 3) {
				strip.setPixelColor(i + q, 0);        //turn every third pixel off
			}
		}
	}
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t ClockLED::Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	else if (WheelPos < 170) {
		WheelPos -= 85;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	else {
		WheelPos -= 170;
		return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	}
}

void ClockLED::test1()
{
	colorWipe(strip.Color(255, 0, 0), 30); // Red
	colorWipe(strip.Color(0, 255, 0), 30); // Green
	colorWipe(strip.Color(0, 0, 255), 30); // Blue
}

void ClockLED::test2()
{
	rainbow(20);
	
}

void ClockLED::test3()
{
	rainbowCycle(20);
}

void ClockLED::test4()
{
	theaterChase(strip.Color(127, 127, 127), 30); // White
	theaterChase(strip.Color(127, 0, 0), 30); // Red
	theaterChase(strip.Color(0, 0, 127), 30); // Blue
	
}

void ClockLED::test5()
{
	theaterChaseRainbow(50);
}

void ClockLED::testAll()
{
	test1();
	test2();
	test3();
	test4();
	test5();
}


ClockLED Clock;

