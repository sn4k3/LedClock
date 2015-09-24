// Photoresistor.h

#ifndef _PHOTORESISTOR_h
#define _PHOTORESISTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Sensor.h"

class PhotoresistorSensor : public SensorClass
{
 protected:
	 unsigned short high;
	 unsigned short low;


 public:
	void init();

	void setValue(byte valuec);

	void manualTune(unsigned short min = 0, unsigned short max = 1023);
	void autotune();

	byte readValue(bool isAutotune, unsigned short min = 0, unsigned short max = 1023);
	unsigned short readValue();
};

extern PhotoresistorSensor Photoresistor;

#endif

