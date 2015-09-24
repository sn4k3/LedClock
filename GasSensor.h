// GasSensor.h

#ifndef _GASSENSOR_h
#define _GASSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Config.h"
#include "Sensor.h"
#include "Alarms.h"



class GasSensorClass : public SensorClass
{
 protected:


 public:
	 GasSensorClass();
	 AlarmClass *alarm;
	void init();
	void on();
	void off();

	unsigned short readValue();
	void loop();
};

extern GasSensorClass GasSensor;

#endif

