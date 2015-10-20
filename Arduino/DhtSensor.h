// TemperatureSensor.h

#ifndef _TEMPERATURESENSOR_h
#define _TEMPERATURESENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor.h"

class DhtSensorClass
{
 protected:
	 float values[2];

 public:
	void init();
	float readTemperature();
	float getTemperature();
	float readHumidity();
	float getHumidity();

};

extern DhtSensorClass DhtSensor;

#endif

