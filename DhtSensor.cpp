// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

#include "DhtSensor.h"
#include "DHT.h"

DHT dht(DHT_DATA_PIN, DHT_TYPE);


void DhtSensorClass::init()
{
	dht.begin();
}

float DhtSensorClass::readTemperature()
{
	// Read temperature as Celsius (the default)
	values[0] = dht.readTemperature();
	return values[0];
}

float DhtSensorClass::readHumidity()
{
	values[1] = dht.readHumidity();
	return values[1];
}

float DhtSensorClass::getTemperature()
{
	return values[0];
}

float DhtSensorClass::getHumidity()
{
	return values[1];
}


DhtSensorClass DhtSensor;

