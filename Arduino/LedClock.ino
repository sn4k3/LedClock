#ifdef _VMDEBUG
#include <MemoryFree.h>
#endif 


#include "Config.h"


#include <EEPROM.h>
#include <Wire.h>
#include "SPI.h"
#include <Time.h>
#include <DS3232RTC.h>
#include <DHT.h>
//#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#include "Timer.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <SoftwareSerial.h>
#include <DS1803.h>

#include "Commands.h"
#include "Alarms.h"
#include "GasSensor.h"
#include "DhtSensor.h"
#include "Display.h"
#include "Clock.h"
#include "PhotoresistorSensor.h"
#include "Buzzer.h"
#include "Pir.h"
#include "radio.h"
#include "TEA5767.h"
#include "RadioFM.h"

//#include <JeeLib.h>

//ISR(WDT_vect) { Sleepy::watchdogEvent(); } // Setup the watchdog

Timer t;


void clock_loop_callback()
{
	Clock.loop();
	Display.render();
}

void clock_setbrightness_callback()
{
	if (Settings.ledbrightness == 0)
	{
		Clock.setBrightnessFromPhotoresistor();
	}
}

void dht_callback()
{
	for (byte i = 0; i < 5; i++)
	{
		float humidity = DhtSensor.readHumidity();
		if (!isnan(humidity) && humidity > 0)
			break;
		delay(100);
		t.update();
	}
	
	for (byte i = 0; i < 5; i++)
	{
		float temperature = DhtSensor.readTemperature();
		if (!isnan(temperature) && temperature > 0)
			break;
		delay(100);
		t.update();
	}
}

void mq2_callback()
{
	if (!Settings.gas_sensor)
		return;

	GasSensor.loop();
}


void setup() {
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
	pinMode(LED_DEBUG_PIN, OUTPUT);
	digitalWrite(LED_DEBUG_PIN, HIGH);
	delay(2000);
	digitalWrite(LED_DEBUG_PIN, LOW);


	Serial.begin(9600);

	while (!Serial) {
		// wait for serial port to connect. Needed for Leonardo only
	}

	DEBUG_PRINTLN(F("INIT"));

	showMem();
	setSyncProvider(RTC.get);   // the function to get the time from the RTC

	SettingsConfig.load();
	Commands.init();
	Alarms.init();
	Buzzer.init();
	Photoresistor.init();
	DhtSensor.init();
	Pir.init();
	GasSensor.init();
	dht_callback();
	Alarms.add(GasSensor.alarm);
	Radio.init();
	Display.init();
	Clock.init();
	
	// Adjust seconds to match the real clock
	unsigned int seconds = second();
	DELAY_FUNC(50);
	while (seconds == second())
	{
		DELAY_FUNC(50);
	}

	clock_loop_callback();
	
	t.every(CLOCK_REPEAT_INTERVAL,			clock_loop_callback);
	t.every(PHOTORESISTOR_REPEAT_INTERVAL,	clock_setbrightness_callback);
	t.every(DHT_REPEAT_INTERVAL,			dht_callback);
	t.every(MQ2_REPEAT_INTERVAL,			mq2_callback);

	

	showMem();
	DEBUG_PRINTLN(F("INIT OVER"));
}


// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
	Commands.loop();
	Alarms.loop();

	t.update();
	//Sleepy::loseSomeTime(200);
	DELAY_FUNC(100);
}

