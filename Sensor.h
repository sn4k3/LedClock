// Sensor.h

#ifndef _SENSOR_h
#define _SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Config.h"

class SensorClass
{
 protected:
	 unsigned short value;

 public:
	virtual ~SensorClass()
	{
	}

	virtual void init();
	virtual void loop();

	virtual unsigned short readValue();
	virtual unsigned short getValue();
};

extern SensorClass Sensor;

#endif

