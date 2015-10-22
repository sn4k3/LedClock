#include "RadioFM.h"

#include <Wire.h>

#include "radio.h"
#include "TEA5767.h"
#include <DS1803.h>
#include <Display.h>

TEA5767  radio;
DS1803 pot(0x28);

#define POT_MAX RADIO_MAX_VOLUME

void RadioClass::init()
{
	pinMode(RADIO_TRANSISTOR_PIN, OUTPUT);
}


void RadioClass::on()
{
	if (state)
		return;
	
	state = true;
	digitalWrite(RADIO_TRANSISTOR_PIN, HIGH);
	delay(100);
	radio.init();

	radio.setMono(false);
	radio.setMute(false);

	if(Settings.radioLastFrequency > 0)
	{
		delay(100);
		radio.setFrequency(Settings.radioLastFrequency);
		delay(50);
		radio.setFrequency(Settings.radioLastFrequency);
	}

	mute(false);
	Display.invalidate_radio();
}


void RadioClass::off()
{
	if (!state)
		return;

	state = false;
	radio.term();
	digitalWrite(RADIO_TRANSISTOR_PIN, LOW);

	Display.invalidate_radio();
}

void RadioClass::setFrequency(unsigned int frequency)
{
	Settings.radioLastFrequency = frequency;
	if(!state)
	{
		on();
	}
	else
	{
		radio.setFrequency(frequency);
	}
	
	//radio.getRadioInfo(this->info);
	/*Serial.println(this->info->active);
	Serial.println(this->info->mono);
	Serial.println(this->info->rds);
	Serial.println(this->info->rssi); // Quality x of 16
	Serial.println(this->info->stereo);
	Serial.println(this->info->tuned);*/

	Display.invalidate_radio();

	SettingsConfig.save();
}

void RadioClass::setVolume(short vol)
{
	if (Settings.radioVolume == vol)
		return;
	byte oldVolume = Settings.radioVolume;
	Settings.radioVolume = constrain(vol, 0, POT_MAX);
	if (oldVolume == Settings.radioVolume)
		return;

	mute(Settings.radioVolume == 0);
	SettingsConfig.save();
}

void RadioClass::volumeUp()
{
	setVolume(Settings.radioVolume + 2);
}

void RadioClass::volumeDown()
{
	setVolume(Settings.radioVolume - 2);
}

void RadioClass::mute(bool ismute)
{
	if(ismute)
	{
		bMute = true;
		radio.setMute(true);
		pot.setPot(0, 0);
	}
	else
	{
		bMute = false;
		pot.setPot(Settings.radioVolume, 0);
		radio.setMute(false);
	}
}

void RadioClass::toogleMute()
{
	mute(!bMute);
}

bool RadioClass::getState()
{
	return state;
}

RadioClass Radio;