#ifndef Buffer_h
#define Buffer_h

#include "Arduino.h"
#include "Types.h"

class Buffer
{
	public:
	Buffer();
	boolean isEmpty();
	boolean store(xbee_data data);
	boolean read0(xbee_data *data);
	boolean read1(xbee_data *data);
	void showBuffer();
};

#endif