#include "SettingsConfig.h"
#include <EEPROM.h>
#include "Clock.h"

SettingsStruct Settings = {
	CONFIG_VERSION,
	false,
	{ ClockStyle_DEFAULT, ClockStyle_DEFAULT, ClockStyle_CURRENT },
	{ NEOCOLOR(255, 0, 0), NEOCOLOR(0, 0, 255), NEOCOLOR(0, 255, 0) },
	0,
	{1023, 0},
	false,
	0,
	75
};

void SettingsConfigClass::init()
{
	DEBUG_PRINT(F("Settings load: "))
	DEBUG_PRINTLN(load());
}

bool SettingsConfigClass::load() {
	for (unsigned int i = 0; i < strlen(CONFIG_VERSION); i++)
	{
		if (EEPROM.read(CONFIG_START + i) != CONFIG_VERSION[i])
			return false;
	}

	for (unsigned int t = 0; t<sizeof(Settings); t++)
		*((char*)&Settings + t) = EEPROM.read(CONFIG_START + t);

	return true;
}

void SettingsConfigClass::save() {
	for (unsigned int t = 0; t<sizeof(Settings); t++)
		EEPROM.write(CONFIG_START + t, *((char*)&Settings + t));
}


SettingsConfigClass SettingsConfig;

