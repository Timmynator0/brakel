// Scheduler
#ifndef _Scheduler_h_
#define _Scheduler_h_

typedef struct
{
  void (*handler)(void);
  unsigned long interval;
  unsigned char id;
  bool isActive;
  unsigned long counter;
} SCHEDULER_EVENT_STRUCT; 

// Defines
#define SCHEDULER_MAX_NUMBER_OF_EVENTS 10
#define SCHEDULER_INTERVAL 100

// Global parameters
static unsigned long previousMilliSeconds = 0;
static SCHEDULER_EVENT_STRUCT schedulerEvents[SCHEDULER_MAX_NUMBER_OF_EVENTS];

// Function prototypes
bool addSchedulerEvent( void(*event)(void), unsigned long interval, unsigned char id );
void initScheduler(void);
bool removeSchedulerEvent(unsigned char id);
void handleScheduler();

#endif