#include "Arduino.h" 
#include "Buffer.h"
#include "BufferManager.h"
#include "Types.h"

#define SDCARD  0
#define DATABASE 1

Buffer buffer;
volatile boolean wrLock = false;
volatile boolean rdLock = false;
	
BufferManager::BufferManager()
{
	
}

boolean BufferManager::store(xbee_data data)
{
	while(rdLock)
  {
    ;
  }
  wrLock = true;
  boolean temp = buffer.store(data);
  wrLock = false;
  return temp;
}

boolean BufferManager::read(xbee_data *data, char process)
{
	if(process == SDCARD)
  {
    while(wrLock)
    {
      ;
    }
    rdLock = true;
    boolean temp = buffer.read0(data);
    rdLock = false;
    return temp;
  }
  else if(process == DATABASE)
  {
    while(wrLock)
    {
      ;
    }
    rdLock = true;
    boolean temp = buffer.read1(data);
    rdLock = false;
    return temp;
  }
}

boolean isEmpty()
{
	return buffer.isEmpty();
}

//
// Show buffer, for debugging
//
void BufferManager::showBuffer()
{
  buffer.showBuffer();
}