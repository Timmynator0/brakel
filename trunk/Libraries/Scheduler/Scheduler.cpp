#include <Scheduler.h>
#include "Arduino.h"
bool schedulerLock = false;

// 
// Dispatch all schedular events
//
void handleScheduler()
{
	if(!schedulerLock)
	{
	//Serial.println("scheduler handler");
		for( unsigned char idx = 0; idx < SCHEDULER_MAX_NUMBER_OF_EVENTS; idx++ )
		{
			if( schedulerEvents[idx].isActive )
			{
				if( schedulerEvents[idx].counter < schedulerEvents[idx].interval )
				{
					schedulerEvents[idx].counter++;
				}
				else
				{
					schedulerEvents[idx].handler();
					schedulerEvents[idx].counter = 0;
				}
			}
		}
	}
}

//
// Init scheduler
//
void initScheduler(void)
{
  for( unsigned char idx = 0; idx < SCHEDULER_MAX_NUMBER_OF_EVENTS; idx++ )
  {
    schedulerEvents[idx].isActive = false;
  } 
}

//
// Remove scheduler event op basis van 'id'
//
bool removeSchedulerEvent(unsigned char id)
{
  bool retVal = false;
  
  for( unsigned char idx = 0; idx < SCHEDULER_MAX_NUMBER_OF_EVENTS; idx++ )
  {
    if(id == schedulerEvents[idx].id)
    {
      schedulerEvents[idx].isActive = false;
      retVal = true;
    }
  }
  return retVal; 
}

//
// Voeg scheduler event toe op eerst volgende lege plek
//
bool addSchedulerEvent( void(*event)(void), 
  unsigned long interval, 
  unsigned char id )
{
  bool retVal = false;
  
  for( unsigned char idx = 0; idx < SCHEDULER_MAX_NUMBER_OF_EVENTS && !retVal; idx++ )
  {
    if(false == schedulerEvents[idx].isActive)
    { 
      schedulerEvents[idx].handler = event;
      schedulerEvents[idx].interval = interval;
      schedulerEvents[idx].id = id;
      schedulerEvents[idx].isActive = true;
      schedulerEvents[idx].counter = 0;
      retVal = true;
    }
  }
  return retVal;
}
