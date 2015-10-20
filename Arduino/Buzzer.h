#ifndef _BUZZER_h
#define _BUZZER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Config.h"

class BuzzerClass
{
public:
	bool haveAlarm;

	void init();
	void beep();
	void alarm();
};

extern BuzzerClass Buzzer;

#endif