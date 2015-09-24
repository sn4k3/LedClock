// Alarms.h

#ifndef _ALARMS_h
#define _ALARMS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define MAX_ALARMS 10

class AlarmClass
{
private:
	unsigned long startTime;
public:
	AlarmClass();
	void init();
	// True for disable alarm when detect motion, otherwise false
	bool disableOnMotion;

	// Auto disable alarm after x seconds of waiting
	unsigned int disableTimeout;

	// The required time alarm must beep before can get disable
	unsigned int disableAfterTime;

	bool disable(bool force = false);
	bool canDisable();
	bool trigger();
	bool loop();

	void beep();

	inline bool isOn();
	inline bool isOff();
};

class AlarmsClass
{
 public:
	AlarmClass *alarms[MAX_ALARMS];
	void init();
	void loop();

	// return index, if there are no space for alarms return -1
	short add(AlarmClass *alarm);
};

extern AlarmsClass Alarms;

#endif

