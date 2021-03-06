// Commands.h

#ifndef _COMMANDS_h
#define _COMMANDS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Config.h"
#include <SoftwareSerial.h>

#define COMMAND_PREFIX "CMD"

#define COMMAND_SETTIME_PREFIX ""COMMAND_PREFIX" SETTIME S"
#define COMMAND_SETTIME_SYNTAX ""COMMAND_SETTIME_PREFIX"<YY><MM><DD><hh><mm><ss>"

#define COMMAND_POWERSAVING_PREFIX ""COMMAND_PREFIX" POWERSAVING"
#define COMMAND_POWERSAVING_SYNTAX ""COMMAND_POWERSAVING_PREFIX" <0/1>"

#define COMMAND_GASSENSOR_PREFIX ""COMMAND_PREFIX" GASSENSOR"
#define COMMAND_GASSENSOR_SYNTAX ""COMMAND_GASSENSOR_PREFIX" <0/1>"

#define COMMAND_RADIO_PREFIX ""COMMAND_PREFIX" RADIO"
#define COMMAND_RADIO_SYNTAX ""COMMAND_RADIO_PREFIX" <on|off|volup|voldown|vol 0-10|next|previous|back|forward|freq xxx>"

#define COMMAND_CLOCKSTYLE_PREFIX ""COMMAND_PREFIX" CLOCKSTYLE"
#define COMMAND_CLOCKSTYLE_SYNTAX ""COMMAND_CLOCKSTYLE_PREFIX" <h|m|s> <0|1|2>"

#define COMMAND_CLOCKCOLOR_PREFIX ""COMMAND_PREFIX" CLOCKCOLOR"
#define COMMAND_CLOCKCOLOR_SYNTAX ""COMMAND_CLOCKCOLOR_PREFIX" <h|m|s> <r> <b> <b>"

#define COMMAND_CLOCKBRIGHTNESS_PREFIX ""COMMAND_PREFIX" CLOCKBRIGHTNESS"
#define COMMAND_CLOCKBRIGHTNESS_SYNTAX ""COMMAND_CLOCKBRIGHTNESS_PREFIX" <0-255>"

#define COMMAND_CLOCKBRIGHTNESSCALIBRATION_PREFIX ""COMMAND_PREFIX" CLOCKBRIGHTNESSCALIBRATION"
#define COMMAND_CLOCKBRIGHTNESSCALIBRATION_SYNTAX ""COMMAND_CLOCKBRIGHTNESSCALIBRATION_PREFIX" <0>"

#define COMMAND_CLOCKLEDTEST_PREFIX ""COMMAND_PREFIX" CLOCKLEDTEST"
#define COMMAND_CLOCKLEDTEST_SYNTAX ""COMMAND_CLOCKLEDTEST_PREFIX" <1-9>"



class CommandsClass
{
 protected:


 public:
	void init();
	void loop();
	bool parse(const char *command);
};

extern CommandsClass Commands;
extern SoftwareSerial BTSerial;

#endif

