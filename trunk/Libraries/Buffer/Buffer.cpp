#include "Arduino.h" 
#include "Buffer.h"
#include <Types.h>

#define bufferSize 25
xbee_data InternalBuffer[bufferSize] = {0,};
xbee_data *pRdBuffer = InternalBuffer;
xbee_data *pRdBuffer2 = InternalBuffer;
xbee_data *pWrBuffer = InternalBuffer;
	
Buffer::Buffer()
{
	
}

boolean Buffer::store(xbee_data data)
{
	boolean retval = false;
  xbee_data *savedPtr = pWrBuffer;
  
  // increment temp pointer
  if( savedPtr == &(InternalBuffer[bufferSize-1]) )
    savedPtr = InternalBuffer;
  else
    savedPtr++;

  // 
  if( savedPtr != pRdBuffer  && savedPtr != pRdBuffer2)
  {
    *pWrBuffer = data;
    if( pWrBuffer == &(InternalBuffer[bufferSize-1]) )
      pWrBuffer = InternalBuffer;
    else
      pWrBuffer++;
      
    retval = true;
  }
  
  return retval;
}

boolean Buffer::read0(xbee_data *data)
{
	boolean retval = false;  
  if( pRdBuffer != pWrBuffer )
  {
    *data = *pRdBuffer;
    
    if( pRdBuffer == &InternalBuffer[bufferSize-1] )
      pRdBuffer = InternalBuffer;
    else
      pRdBuffer++;
    
    retval = true;
  }

  return retval; 
}

boolean Buffer::read1(xbee_data *data)
{
	boolean retval = false;  
  if( pRdBuffer2 != pWrBuffer )
  {
    *data = *pRdBuffer2;
    
    if( pRdBuffer2 == &InternalBuffer[bufferSize-1] )
      pRdBuffer2 = InternalBuffer;
    else
      pRdBuffer2++;
    
    retval = true;
  }

  return retval; 
}

boolean Buffer::isEmpty()
{
	return pRdBuffer == pWrBuffer && pRdBuffer2 == pWrBuffer;
}

//
// Show buffer, for debugging
//
void Buffer::showBuffer()
{
  Serial.println("--------------------------------------------");
  Serial.print("Buffer:\t\t");
  for(int idx = 0; idx < bufferSize; idx++ )
  {
    Serial.print((char)InternalBuffer[idx].temperature); Serial.print(" ");
  }
  Serial.println();
  Serial.print("pWrBuffer:\t");
  int size = pWrBuffer-InternalBuffer;
  for( int idx = 0; idx < size; idx++ )
    Serial.print(". ");
  Serial.print("^");

  Serial.println();
  Serial.print("pRdBuffer:\t");
  size = pRdBuffer-InternalBuffer;
  for( int idx = 0; idx < size; idx++ )
    Serial.print(". ");
  Serial.print("^");
  
  Serial.println();
  Serial.print("pRdBuffer2:\t");
  size = pRdBuffer2 - InternalBuffer;
  for(int idx = 0; idx < size; idx++)
	Serial.print(". ");
  Serial.print("^");

  Serial.println();
  Serial.println();
}