#ifndef Buffer_h
#define Buffer_h

#include "Arduino.h"
#include "Types.h"

#define bufferSize 50
enum readers
{
	SDCARD = 0,
	DATABASE = 1
};

class Buffer
{
	public:
	
	Buffer();
	boolean isEmpty(char process);
	boolean store(xbee_data data);
	boolean read0(xbee_data *data);
	boolean read1(xbee_data *data);
	void showBuffer();
};

#endif