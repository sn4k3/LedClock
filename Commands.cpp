// 
// 
// 

#include "Commands.h"
#include "Time.h"
#include <DS3232RTC.h>
#include "Clock.h"
#include "RadioFM.h"
#include "GasSensor.h"
#include "PhotoresistorSensor.h"

SoftwareSerial BTSerial(BLUETOOTH_RX_PIN, BLUETOOTH_TX_PIN); // RX | TX

void CommandsClass::init()
{
	BTSerial.begin(9600);
}

#define READ_DATA_MAXSIZE 50
char inData[READ_DATA_MAXSIZE]; // Allocate some space for the string
char inChar; // Where to store the character read
			 // Index into array; where to store the character
void CommandsClass::loop()
{
	byte index = 0;
	while (BTSerial.available() > 0) // Don't read unless
									 // there you know there is data
	{
		if (index < READ_DATA_MAXSIZE - 1) // One less than the size of the array
		{
			inChar = (char)BTSerial.read(); // Read a character
			inData[index] = inChar; // Store it
			index++; // Increment where to write next
			inData[index] = '\0'; // Null terminate the string
			continue;
		}
		BTSerial.read();
	}

	if (index > 0)
	{
		parse(inData);
	}

	while (Serial.available() > 0) // Don't read unless
								   // there you know there is data
	{
		BTSerial.print((char)Serial.read());
	}
}


bool CommandsClass::parse(const char *command)
{
	Serial.println(command);

	// SET DATE TIME
	byte command_size = strlen(COMMAND_SETTIME_PREFIX);
	byte data_size = strlen(command);
	if (strncmp(command, COMMAND_SETTIME_PREFIX, command_size) == 0) // Set clock date time
	{
		if (data_size < command_size + 12)
		{
			BTSerial.println(F(COMMAND_SETTIME_SYNTAX));
			return true;
		}
		tmElements_t tm;

		char buff[3];
		byte digit = 0;
		for (unsigned short i = command_size; i < READ_DATA_MAXSIZE; i += 2)
		{
			if (command[i] == '\0' || command[i + 1] == '\0') break;
			memcpy(buff, &command[i], 2);
			buff[2] = '\0';

			int number = atoi(buff);
			switch (digit)
			{
			case 0:
				tm.Year = y2kYearToTm(number);
				break;
			case 1:
				tm.Month = number;
				break;
			case 2:
				tm.Day = number;
				break;
			case 3:
				tm.Hour = number;
				break;
			case 4:
				tm.Minute = number;
				break;
			case 5:
				tm.Second = number;
				break;
			default:
				break;
			}

			digit++;
		}

		time_t timeSet = makeTime(tm);

		setTime(timeSet);
		RTC.set(timeSet);
		PROGRAM_PRINTLN(F("OK - Clock datetime set!"));
		Clock.blackLEDs();
		return true;
	}

	// CLOCK TEST
	command_size = strlen(COMMAND_CLOCKLEDTEST_PREFIX);
	if (strncmp(command, COMMAND_CLOCKLEDTEST_PREFIX, command_size) == 0)
	{
		if (data_size < command_size + 2)
		{
			BTSerial.println(F(COMMAND_CLOCKLEDTEST_SYNTAX));
			return true;
		}

		char buff[2];
		memcpy(buff, &command[command_size + 1], 1);
		buff[1] = '\0';

		PROGRAM_PRINTLN(F("OK - Test Started!"));
		byte test = atoi(buff);

		switch (test)
		{
		case 1:
			Clock.test1();
			break;
		case 2:
			Clock.test2();
			break;
		case 3:
			Clock.test3();
			break;
		case 4:
			Clock.test4();
			break;
		case 5:
			Clock.test5();
			break;
		case 6:
			Clock.testAll();
			break;
		}

		Clock.blackLEDs();


		return true;
	}

	// POWER SAVING
	command_size = strlen(COMMAND_POWERSAVING_PREFIX);
	if (strncmp(command, COMMAND_POWERSAVING_PREFIX, command_size) == 0)
	{
		if (data_size < command_size + 2)
		{
			BTSerial.println(F(COMMAND_POWERSAVING_SYNTAX));
			return true;
		}

		char buff[2];
		memcpy(buff, &command[command_size + 1], 1);
		buff[1] = '\0';

		Settings.powersaving = (atoi(buff) >= 1);

		PROGRAM_PRINTLN(F("OK - Power saving set!"));
		SettingsConfig.save();
		return true;
	}

	// GAS SENSOR
	command_size = strlen(COMMAND_GASSENSOR_PREFIX);
	if (strncmp(command, COMMAND_GASSENSOR_PREFIX, command_size) == 0)
	{
		if (data_size < command_size + 2)
		{
			BTSerial.println(F(COMMAND_GASSENSOR_SYNTAX));
			return true;
		}

		char buff[2];
		memcpy(buff, &command[command_size + 1], 1);
		buff[1] = '\0';

		Settings.gas_sensor = (atoi(buff) >= 1);
		GasSensor.init();

		PROGRAM_PRINTLN(F("OK - Gas Sensor set!"));
		SettingsConfig.save();
		return true;
	}

	// RADIO
	command_size = strlen(COMMAND_RADIO_PREFIX);
	if (strncmp(command, COMMAND_RADIO_PREFIX, command_size) == 0)
	{
		if (data_size < command_size + 3)
		{
			BTSerial.println(F(COMMAND_RADIO_SYNTAX));
			return true;
		}

		char buff[10];
		byte lastWordIndex = getNextWord(command, command_size + 1, buff, 10);


		if (strcmp(buff, "on") == 0 || strcmp(buff, "ON") == 0)
		{
			Radio.on();
			Serial.println(F("ON"));
		}
		else if (strcmp(buff, "off") == 0 || strcmp(buff, "OFF") == 0)
		{
			Radio.off();
		}
		else if (strcmp(buff, "freq") == 0 || strcmp(buff, "FREQ") == 0)
		{
			getNextWord(command, lastWordIndex, buff, 10);
			if (buff[0] != '\0')
				Radio.setFrequency(atoi(buff));
		}

		else if (strcmp(buff, "vol") == 0 || strcmp(buff, "VOL") == 0)
		{
			getNextWord(command, lastWordIndex, buff, 10);
			if (buff[0] != '\0')
			{
				if (buff[0] == '+' || strcmp(buff, "up") == 0 || strcmp(buff, "UP") == 0)
				{
					Radio.volumeUp();
				}
				else if (buff[0] == '-' || strcmp(buff, "down") == 0 || strcmp(buff, "DOWN") == 0)
				{
					Radio.volumeDown();
				}
				else
				{
					Radio.setVolume(atoi(buff));
				}
			}
		}
		else if (strcmp(buff, "mute") == 0 || strcmp(buff, "MUTE") == 0)
		{
			getNextWord(command, lastWordIndex, buff, 10);
			if (buff[0] != '\0')
			{
				if(buff[0] == '1')
				{
					Radio.mute(true);
				}
				else if (buff[0] == '0')
				{
					Radio.mute(false);
				}
				else
				{
					Radio.toogleMute();
				}
			}
			else
			{
				Radio.toogleMute();
			}
		}


		PROGRAM_PRINTLN(F("OK - Radio set!"));
		SettingsConfig.save();
		return true;
	}

	// CLOCK STYLE
	command_size = strlen(COMMAND_CLOCKSTYLE_PREFIX);
	if (strncmp(command, COMMAND_CLOCKSTYLE_PREFIX, command_size) == 0)
	{
		if (data_size < command_size + 4)
		{
			BTSerial.println(F(COMMAND_CLOCKSTYLE_SYNTAX));
			return true;
		}

		byte index = 0; // h | m | s

		switch (command[command_size + 1])
		{
		case 'h':
		case 'H':
		default:
			index = 0;
			break;
		case 'm':
		case 'M':
			index = 1;
			break;
		case 's':
		case 'S':
			index = 2;
			break;
		}

		char buff[2];
		memcpy(buff, &command[command_size + 3], 1);
		buff[1] = '\0';

		Settings.clock_style[index] = constrain(atoi(buff), 0, 2);

		PROGRAM_PRINTLN(F("OK - Clock style set!"));
		SettingsConfig.save();
		return true;
	}

	// CLOCK COLOR
	command_size = strlen(COMMAND_CLOCKCOLOR_PREFIX);
	if (strncmp(command, COMMAND_CLOCKCOLOR_PREFIX, command_size) == 0)
	{
		if (data_size < command_size + 8)
		{
			BTSerial.println(F(COMMAND_CLOCKCOLOR_SYNTAX));
			return true;
		}

		byte index = 0; // h | m | s

		switch (command[command_size + 1])
		{
		case 'h':
		case 'H':
		default:
			index = 0;
			break;
		case 'm':
		case 'M':
			index = 1;
			break;
		case 's':
		case 'S':
			index = 2;
			break;
		}

		char buff[12];
		memcpy(buff, &command[command_size + 3], 11);
		buff[11] = '\0';

		Serial.println(buff);

		char *pch;
		pch = strtok(buff, " ");
		byte count = 0;
		byte rgb[3];
		while (pch != NULL)
		{
			if (index == 3)
				break;

			rgb[count] = constrain(atoi(pch), 0, 255);
			pch = strtok(NULL, " ");
			count++;
		}

		Settings.clock_color[index] = NEOCOLOR(rgb[0], rgb[1], rgb[2]);

		PROGRAM_PRINTLN(F("OK - Clock color set!"));
		SettingsConfig.save();
		return true;
	}

	// LED BRIGHTNESS CALIBRATION
	command_size = strlen(COMMAND_CLOCKBRIGHTNESSCALIBRATION_PREFIX);
	if (strncmp(command, COMMAND_CLOCKBRIGHTNESSCALIBRATION_PREFIX, command_size) == 0)
	{
		if (data_size < command_size + 2)
		{
			BTSerial.println(F(COMMAND_CLOCKBRIGHTNESSCALIBRATION_SYNTAX));
			return true;
		}

		/*char buff[2];
		memcpy(buff, &command[command_size + 1], 1);
		buff[1] = '\0';
		}*/

		Settings.ledbrightness_calibration[0] = 1023;
		Settings.ledbrightness_calibration[1] = 0;
		SettingsConfig.save();
		Photoresistor.init();


		PROGRAM_PRINTLN(F("OK - Clock brightness calibration set!"));
		return true;
	}

	// LED BRIGHTNESS
	command_size = strlen(COMMAND_CLOCKBRIGHTNESS_PREFIX);
	if (strncmp(command, COMMAND_CLOCKBRIGHTNESS_PREFIX, command_size) == 0)
	{
		if (data_size < command_size + 2)
		{
			BTSerial.println(F(COMMAND_CLOCKBRIGHTNESS_SYNTAX));
			return true;
		}

		char buff[4];
		memcpy(buff, &command[command_size + 1], 3);
		buff[3] = '\0';

		Settings.ledbrightness = constrain(atoi(buff), 0, 255);
		if (Settings.ledbrightness > 0)
		{
			Clock.setBrightness(Settings.ledbrightness);
		}

		PROGRAM_PRINTLN(F("OK - Clock brightness set!"));
		SettingsConfig.save();
		return true;
	}

	return false;
}


CommandsClass Commands;

