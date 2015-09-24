// 
// 
// 
#include "Alarms.h"
#include "Buzzer.h"
AlarmClass::AlarmClass()
{
	init();
}

void AlarmClass::init()
{
	startTime = 0;
	disableTimeout = 0;
	disableAfterTime = 0;
	disableOnMotion = false;
}

/*
	Alarm class
*/
bool AlarmClass::trigger()
{
	if(isOn())
	{
		return false;
	}

	startTime = millis();
	return true;
}

bool AlarmClass::disable(bool force)
{
	if (isOff())
	{
		return false;
	}

	if(!force)
	{
		if (!canDisable())
			return false;
	}

	startTime = 0;
	return true;
}

bool AlarmClass::canDisable()
{
	if (isOff())
	{
		return false;
	}

	
	if (disableAfterTime == 0) return true;
	if ((millis() - startTime) >= disableAfterTime)
	{
		return true;
	}

	return false;
}

bool AlarmClass::loop()
{
	if (isOff()) return false;

	if(disableTimeout > 0)
	{
		if ((millis() - startTime) >= disableTimeout)
		{
			return disable();
		}
	}
	beep();	

	return true;
}

void AlarmClass::beep()
{
	Buzzer.alarm();
}


inline  bool AlarmClass::isOn()
{
	return (startTime > 0);
}

inline bool AlarmClass::isOff()
{
	return (startTime == 0);
}



/*
	Alarm manager class
*/
void AlarmsClass::init()
{
	for (byte i = 0; i < MAX_ALARMS; i++)
	{
		alarms[i] = NULL;
	}

}

void AlarmsClass::loop()
{
	for (byte i = 0; i < MAX_ALARMS; i++)
	{
		if (!alarms[i]) continue;
		alarms[i]->loop();
	}

}

short AlarmsClass::add(AlarmClass* alarm)
{
	byte i = 0;
	for (i = 0; i < MAX_ALARMS; i++)
	{
		if (alarms[i]) continue;
		alarms[i] = alarm;
		return i;
	}

	return -1;
}

AlarmsClass Alarms;

