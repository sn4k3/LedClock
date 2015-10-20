#ifndef _PIR_h
#define _PIR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Config.h"

class PirClass
{
private:
	bool state;
public:
	

	void init();
	bool getState();

	void toogleState();
};


extern PirClass Pir;

#endif