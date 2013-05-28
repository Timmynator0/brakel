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
  noInterrupts();
  wrLock = true;
  interrupts();
  boolean temp = buffer.store(data);
  noInterrupts();
  wrLock = false;
  interrupts();
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
	noInterrupts();
    rdLock = true;
	interrupts();
    boolean temp = buffer.read0(data);
	noInterrupts();
    rdLock = false;
	interrupts();
    return temp;
  }
  else if(process == DATABASE)
  {
    while(wrLock)
    {
      ;
    }
	noInterrupts();
    rdLock = true;
	interrupts();
    boolean temp = buffer.read1(data);
	noInterrupts();
    rdLock = false;
	interrupts();
    return temp;
  }
}

boolean BufferManager::isEmpty(char process)
{
	return buffer.isEmpty(process);
}

//
// Show buffer, for debugging
//
void BufferManager::showBuffer()
{
  buffer.showBuffer();
}