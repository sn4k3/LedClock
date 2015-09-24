#include "GasSensor.h"

#include "Buzzer.h"

GasSensorClass::GasSensorClass()
{
	alarm = new AlarmClass();
	alarm->init();
	alarm->disableTimeout = 0;
	alarm->disableAfterTime = 10000;
	alarm->disableOnMotion = false;
}

void GasSensorClass::init()
{
	
	pinMode(MQ2_TRANSISTOR_PIN, OUTPUT);
	value = 0;
	if (Settings.gas_sensor)
		on();
	else
	{
		off();
	}
}

void GasSensorClass::on()
{
	digitalWrite(MQ2_TRANSISTOR_PIN, HIGH);
}

void GasSensorClass::off()
{
	alarm->disable(true);
	digitalWrite(MQ2_TRANSISTOR_PIN, LOW);
}

unsigned short GasSensorClass::readValue()
{
	value = analogRead(MQ2_ANALOG_PIN);
	return value;
}

void GasSensorClass::loop()
{
	unsigned short value = readValue();
	if (value >= MQ2_THRESHOLD)
	{
		alarm->trigger();
		alarm->loop();
	}
	else
	{
		alarm->disable();
	}
}

GasSensorClass GasSensor = GasSensorClass();

