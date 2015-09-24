#include "Pir.h"

#include "Buzzer.h"

void pir_interrupt()
{
	Pir.toogleState();
}

void PirClass::init()
{
	attachInterrupt(0, pir_interrupt, CHANGE);
}


bool PirClass::getState()
{
	return state;
}

void PirClass::toogleState()
{
	state = !state;
	if (state)
	{
		Buzzer.haveAlarm = false;
	}
}

PirClass Pir;