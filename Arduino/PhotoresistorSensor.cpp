/*
PHOTORESISTOR

Use a photoresistor (light sensor) to control the brightness.

Hardware connections:

Photo resistor:

Connect one side of the photoresistor to 5 Volts (5V).
Connect the other side of the photoresistor to ANALOG pin 0.
Connect a 10K resistor between ANALOG pin 0 and GND.

This creates a voltage divider, with the photoresistor one
of the two resistors. The output of the voltage divider
(connected to A0) will vary with the light level.
*/

#include "PhotoresistorSensor.h"
#include "Config.h"

void PhotoresistorSensor::init()
{
	low = Settings.ledbrightness_calibration[0];
	high = Settings.ledbrightness_calibration[1];
}

void PhotoresistorSensor::setValue(byte valuec)
{
	value = constrain(valuec, 0, 255);
}

void PhotoresistorSensor::manualTune(unsigned short min, unsigned short max)
{
	// As we mentioned above, the light-sensing circuit we built
	// won't have a range all the way from 0 to 1023. It will likely
	// be more like 300 (dark) to 800 (light). If you run this sketch
	// as-is, the LED won't fully turn off, even in the dark.

	// You can accommodate the reduced range by manually 
	// tweaking the "from" range numbers in the map() function.
	// Here we're using the full range of 0 to 1023.
	// Try manually changing this to a smaller range (300 to 800
	// is a good guess), and try it out again. If the LED doesn't
	// go completely out, make the low number larger. If the LED
	// is always too bright, make the high number smaller.

	// Remember you're JUST changing the 0, 1023 in the line below!

	value = map(value, min, max, LED_MIN_BRIGHTNESS, 255);
	value = constrain(value, LED_MIN_BRIGHTNESS, 255);
}

void PhotoresistorSensor::autotune()
{
	// As we mentioned above, the light-sensing circuit we built
	// won't have a range all the way from 0 to 1023. It will likely
	// be more like 300 (dark) to 800 (light).

	// In the manualTune() function above, you need to repeatedly
	// change the values and try the program again until it works.
	// But why should you have to do that work? You've got a
	// computer in your hands that can figure things out for itself!

	// In this function, the Arduino will keep track of the highest
	// and lowest values that we're reading from analogRead().

	// If you look at the top of the sketch, you'll see that we've
	// initialized "low" to be 1023. We'll save anything we read
	// that's lower than that:

	bool changed = false;
	if (value < low)
	{
		low = value;
		changed = true;
	}

	// We also initialized "high" to be 0. We'll save anything
	// we read that's higher than that:

	if (value > high)
	{
		high = value;
		changed = true;
	}

	if(changed)
	{
		Settings.ledbrightness_calibration[0] = low;
		Settings.ledbrightness_calibration[1] = high;
		SettingsConfig.save();
	}

	// Once we have the highest and lowest values, we can stick them
	// directly into the map() function. No manual tweaking needed!

	// One trick we'll do is to add a small offset to low and high,
	// to ensure that the LED is fully-off and fully-on at the limits
	// (otherwise it might flicker a little bit).

	value = map(value, low, high, LED_MIN_BRIGHTNESS, 255);
	value = constrain(value, LED_MIN_BRIGHTNESS, 255);
}

byte PhotoresistorSensor::readValue(bool isAutotune, unsigned short min, unsigned short max)
{
	value = smoothAnalogRead(PHOTORESISTOR_ANALOG_PIN, 3);
	if (isAutotune)
	{
		autotune();
	}
	else
	{
		manualTune(min, max);
	}
	return value;
}

unsigned short PhotoresistorSensor::readValue()
{
	return readValue(true);
}



PhotoresistorSensor Photoresistor;

