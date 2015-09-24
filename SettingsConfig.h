// SettingsConfig.h

#ifndef _SETTINGSCONFIG_h
#define _SETTINGSCONFIG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Config.h"

struct SettingsStruct {
	char version[9];
	bool powersaving;
	unsigned char clock_style[3]; // Hours:Minutes:Seconds 0 = Default | 1 = Current | 2 = None
	uint32_t clock_color[3]; // Hours:Minutes:Seconds
	byte ledbrightness; // 0 to auto
	unsigned short ledbrightness_calibration[2]; // Autotune calibration
	bool gas_sensor;
	unsigned int radioLastFrequency;
	byte radioVolume;
};

class SettingsConfigClass
{
 public:
	void init();
	bool load();
	void save();
};

extern SettingsConfigClass SettingsConfig;
extern SettingsStruct Settings;

#endif

