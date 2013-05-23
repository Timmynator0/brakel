#ifndef BufferManager_h
#define BufferManager_h

#include "Arduino.h"
#include "Buffer.h"
#include "Types.h"

class BufferManager
{
	public:
	BufferManager();
	boolean read(xbee_data *data, char process);
	boolean store(xbee_data data);
	boolean isEmpty();
	void showBuffer();
};

#endif