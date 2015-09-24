#include "Display.h"
#include <Time.h>
#include "DhtSensor.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(DISPLAY_TFT_CS, DISPLAY_TFT_DC);
//Adafruit_ILI9341 tft = Adafruit_ILI9341(DISPLAY_TFT_CS, DISPLAY_TFT_DC, MISO, SCK, -1, MOSI);


void formatTimeDigits(char strOut[3], int num)
{
	strOut[0] = '0' + (num / 10);
	strOut[1] = '0' + (num % 10);
	strOut[2] = '\0';
}

byte DisplayClass::alignCenterPadding(byte length, byte textSize)
{
	switch (textSize)
	{
	case 3:
		return round((DISPLAY_MAX_TEXT_SIZE3 - length) / 2);
		break;
	case 5:
		return round((DISPLAY_MAX_TEXT_SIZE5 - length) / 2);
		break;
	}

	return 0;
}


void DisplayClass::init()
{
	current_day = 99;
	current_hours[0] = 99;
	current_hours[1] = 99;
	current_hours[2] = 99;

	current_temperature = 0;
	current_humidity = 0;


	tft.begin();
	tft.fillScreen(ILI9341_BLACK);
	tft.setRotation(1);
	/*lcd.begin(20, 4);


	byte charBitmapSize = (sizeof(charBitmap) / sizeof(charBitmap[0]));
	for (byte i = 0; i < charBitmapSize; i++)
	{
		lcd.createChar(i, (uint8_t *)charBitmap[i]);
	}

	lcd.home();
	lcd.print(F("   LED CLOCK v1.0   "));
	lcd.setCursor(0, 1);
	lcd.print(F("By: Tiago Conceicao"));

	lcd.setCursor(0, 2);
	lcd.print(F("Initializing..."));
	lcd.setBacklight(2);*/
}

void DisplayClass::render()
{
	/*tft.setTextSize(2);
	for (int i = 0; i <= 400; i++)
	{
		tft.print((char)i);
	}
	delay(20000);
	return;*/

	byte dayNow = day();
	byte hours = hour();
	byte minutes = minute();
	byte seconds = second();

	char num[3];
	bool newDay = false;

	tft.setCursor(0, 0);
	tft.setTextColor(ILI9341_WHITE);
	if (dayNow != current_day)
	{
		tft.fillRect(0, 0, 320, 30, ILI9341_BLACK);
		tft.setTextSize(3);

		formatTimeDigits(num, dayNow);

		char complete_date[20];
		sprintf(complete_date, "%s %s %i", num, monthStr(month()), year());

		byte padding = alignCenterPadding(strlen(complete_date), 3);
		for (byte i = padding; i > 0; i--)
		{
			tft.print(' ');
		}
		
		tft.print(complete_date);

		current_day = dayNow;
		newDay = true;
	}

	if (newDay)
	{
		tft.fillRect(0, 40, 320, 30, ILI9341_BLACK);
		tft.setTextColor(ILI9341_WHITE);
		tft.setCursor(0, 40);
		tft.setTextSize(3);

		char *buff = dayStr(weekday());

		byte padding = alignCenterPadding(strlen(buff), 3);
		for (byte i = padding; i > 0; i--)
		{
			tft.print(' ');
		}


		tft.print(buff);
	}

	//tft.fillRect(40, 40, 5 * 5 * 10, 50, ILI9341_BLACK);

	tft.setCursor(40, 100);
	tft.setTextSize(5);

	if (hours != current_hours[0])
	{
		tft.setTextColor(ILI9341_BLACK);
		formatTimeDigits(num, current_hours[0]);
		tft.print(num);

		tft.setCursor(40, 100);
		tft.setTextColor(DISPLAY_HOURS_COLOR);
		formatTimeDigits(num, hours);
		tft.print(num);

		current_hours[0] = hours;
		tft.print(':');
	}
	else
	{
		tft.print(F("   "));
	}

	

	/*formatTimeDigits(num, hours);
	tft.print(num);
	tft.print(':');*/

	if (minutes != current_hours[1])
	{
		tft.setTextColor(ILI9341_BLACK);
		formatTimeDigits(num, current_hours[1]);
		tft.print(num);

		tft.setCursor(40, 100);
		tft.setTextColor(DISPLAY_HOURS_COLOR);
		tft.print(F("   "));
		formatTimeDigits(num, minutes);
		tft.print(num);

		current_hours[1] = minutes;
		tft.print(':');
	}
	else
	{
		tft.print(F("   "));
	}


	/*formatTimeDigits(num, minutes);
	tft.print(num);
	tft.print(':');*/

	if (seconds != current_hours[2])
	{
		tft.setTextColor(ILI9341_BLACK);
		formatTimeDigits(num, current_hours[2]);
		tft.print(num);

		tft.setCursor(40, 100);
		tft.setTextColor(DISPLAY_HOURS_COLOR);
		tft.print(F("      "));
		formatTimeDigits(num, seconds);
		tft.print(num);

		current_hours[2] = seconds;
	}

	tft.setCursor(20, 220);
	tft.setTextSize(3);
	
	float value = DhtSensor.getTemperature();
	if (current_temperature != value)
	{
		if (!isnan(value) && value > 0)
		{
			tft.setTextColor(ILI9341_BLACK);
			tft.print(current_temperature);
			tft.setCursor(20, 220);


			tft.setTextColor(DISPLAY_TEMPERATURE_COLOR);
			current_temperature = value;
			tft.print(value);
			tft.print((char)9);
			tft.print('c');
		}
	}


	tft.setCursor(190, 220);
	value = DhtSensor.getHumidity();
	if (current_humidity != value)
	{
		if (!isnan(value) && value > 0)
		{
			tft.setTextColor(ILI9341_BLACK);
			tft.print(current_humidity);
			tft.setCursor(190, 220);


			tft.setTextColor(DISPLAY_TEMPERATURE_COLOR);
			current_humidity = value;
			tft.print(value);
			tft.print('%');
		}
	}
	
}


DisplayClass Display;

