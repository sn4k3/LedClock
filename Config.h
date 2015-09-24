#ifndef _CONFIG_h
#define _CONFIG_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define _VMDEBUG 1

#include "Macros.h"
#include "SettingsConfig.h"

#define LEDCLOCK_MCU_1284p true


#ifndef LEDCLOCK_MCU_1284p
	#define LED_DATA_PIN DD4
	#define DHT_DATA_PIN DD5   // DHT 22  (AM2302)
	#define PHOTORESISTOR_ANALOG_PIN A7
	#define MQ2_ANALOG_PIN A1
	#define MQ2_TRANSISTOR_PIN A0
	#define BLUETOOTH_RX_PIN 7
	#define BLUETOOTH_TX_PIN 8
	#define BUZZER_PIN DD6
	#define PIR_PIN DD2
	#define RADIO_TRANSISTOR_PIN A3
	#define INFRARED_PIN DD12

	#define DISPLAY_TFT_CS 10
	#define DISPLAY_TFT_DC 9
#else
#ifdef ARDUINO_1284P_BOBUINO
	#define LED_DEBUG_PIN 31
	#define LED_DATA_PIN DD4
	#define DHT_DATA_PIN DD5   // DHT 22  (AM2302)
	#define PHOTORESISTOR_ANALOG_PIN A6
	#define MQ2_ANALOG_PIN A5
	#define MQ2_TRANSISTOR_PIN 25
	#define BLUETOOTH_RX_PIN 27
	#define BLUETOOTH_TX_PIN 28
	#define BUZZER_PIN A7
	#define PIR_PIN DD6
	#define RADIO_TRANSISTOR_PIN 26
	#define INFRARED_PIN 24

	#define DISPLAY_TFT_CS SS
	#define DISPLAY_TFT_DC DD7
#else
	#define LED_DEBUG_PIN 15
	#define BLUETOOTH_RX_PIN 22
	#define BLUETOOTH_TX_PIN 21
	#define LED_DATA_PIN DD0
	#define DHT_DATA_PIN DD1   // DHT 22  (AM2302)
	#define PIR_PIN DD3
	#define RADIO_TRANSISTOR_PIN 20
	#define INFRARED_PIN 18

	#define BUZZER_PIN A0
	#define PHOTORESISTOR_ANALOG_PIN A1
	#define MQ2_ANALOG_PIN A2
	#define MQ2_TRANSISTOR_PIN 19
	
	
	

	#define DISPLAY_TFT_CS SS
	#define DISPLAY_TFT_DC 3
#endif
#endif


// Data pin that led data will be written out over

#define LED_MIN_BRIGHTNESS 1
#define CLOCK_REPEAT_INTERVAL 1000

#define PHOTORESISTOR_REPEAT_INTERVAL 2000


#define MQ2_REPEAT_INTERVAL 10000 // 10 seconds
#define MQ2_THRESHOLD 700

#define DHT_TYPE 22   // DHT 22  (AM2302)
#define DHT_REPEAT_INTERVAL 300000 // 5 minutes


#define CONFIG_VERSION "LEDCLOCK"
#define CONFIG_START 0


#endif