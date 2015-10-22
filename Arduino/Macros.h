#ifndef _MACROS_h
#define _MACROS_h

/*
* MARCOS
*/
#define DELAY_FUNC delay

// Define where debug output will be printed.
#ifdef DEBUG_PRINTER
#undef DEBUG_PRINTER
#endif

#define DEBUG_PRINTER Serial


#ifdef DEBUG_PRINT
#undef DEBUG_PRINT
#undef DEBUG_PRINTLN
#endif

// Setup debug printing macros.
#ifdef _VMDEBUG
#include <MemoryFree.h>
#define showMem() DEBUG_PRINTER.print(F("memory = ")); DEBUG_PRINTER.println(freeMemory())
#define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
#define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
#define DEBUG_PRINT(...) {}
#define DEBUG_PRINTLN(...) {}
#define showMem()
#endif

#define PROGRAM_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); BTSerial.print(__VA_ARGS__); }
#define PROGRAM_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); BTSerial.println(__VA_ARGS__); }

#define NEOCOLOR(r, g, b) ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b

inline byte getNextWord(const char *str, byte startIndex, char* output, byte maxSize)
{
	while (str[startIndex] == ' ')
		startIndex++;

	byte i = 0;
	while (str[startIndex] != ' ' && str[startIndex] != '\0' && i < maxSize)
	{
		output[i] = str[startIndex];
		startIndex++;
		i++;
	}

	output[i] = '\0';

	return startIndex;
}

inline unsigned int smoothAnalogRead(byte pin, byte reads = 5)
{
	unsigned int value = 0;
	for (byte i = 0; i < reads; i++)
	{
		value += analogRead(pin);
	}
	return value / reads;
}

inline char *ftoa(char *a, double f, int precision)
{
	long p[] = { 0,10,100,1000,10000,100000,1000000,10000000,100000000 };

	char *ret = a;
	long heiltal = (long)f;
	itoa(heiltal, a, 10);
	while (*a != '\0') a++;
	*a++ = '.';
	long desimal = abs((long)((f - heiltal) * p[precision]));
	itoa(desimal, a, 10);
	return ret;
}

#endif