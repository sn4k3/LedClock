// 
// 
// 

#include "Sensor.h"

void SensorClass::init()
{
	value = 0;
}

void SensorClass::loop() { readValue();  }
unsigned short SensorClass::readValue() { return value;  }
unsigned short SensorClass::getValue()
{
	return value;
}


SensorClass Sensor;

