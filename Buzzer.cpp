#include "Buzzer.h"

void BuzzerClass::init()
{
	haveAlarm = false;
	pinMode(BUZZER_PIN, OUTPUT);
}

void BuzzerClass::beep()
{
	tone(BUZZER_PIN, 160, 300);
}


void BuzzerClass::alarm()
{
	tone(BUZZER_PIN, 800, 250);
	delay(250);
	tone(BUZZER_PIN, 1000, 250);
	delay(250);
}

BuzzerClass Buzzer;
