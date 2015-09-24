#include "RadioFM.h"

#include <Wire.h>

#include "radio.h"
#include "TEA5767.h"
#include <DS1803.h>

TEA5767  radio;
DS1803 pot(0x28);

#define POT_MAX 150

void RadioClass::init()
{
	pinMode(RADIO_TRANSISTOR_PIN, OUTPUT);
}


void RadioClass::on()
{
	Serial.println(state);
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
}


void RadioClass::off()
{
	if (!state)
		return;

	state = false;
	radio.term();
	digitalWrite(RADIO_TRANSISTOR_PIN, LOW);
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
	
	RADIO_INFO info;
	radio.getRadioInfo(&info);
	Serial.println(info.active);
	Serial.println(info.mono);
	Serial.println(info.rds);
	Serial.println(info.rssi); // Quality x of 16
	Serial.println(info.stereo);
	Serial.println(info.tuned);

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


RadioClass Radio;