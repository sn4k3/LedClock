#ifndef _RADIOFM_h
#define _RADIOFM_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "Config.h"

class RadioClass
{
private:
	bool state;
	bool bMute;

public:
	void init();
	void on();
	void off();

	void setFrequency(unsigned int frequency);
	void setVolume(short vol);
	void volumeUp();
	void volumeDown();
	void mute(bool ismute = true);
	void toogleMute();
};

extern RadioClass Radio;

#endif