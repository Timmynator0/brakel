#include <Scheduler.h>

// Scheduler actions 
void action_1(void)
{
  Serial.println("action 1");
}

void action_2(void)
{
  Serial.println("AKTION TWEI");
}

void printSterretjes(void)
{
  Serial.println("**** allemaal sterretjes ****");
}

void printPlusjes(void)
{
  Serial.println("++++++++++++++++");
}


void setup(void)
{
  Serial.begin(9600);
  initScheduler();

  // Voeg enkele scheduler taken toe (max SCHEDULER_MAX_NUMBER_OF_EVENTS, check result!)
  if( true != addSchedulerEvent( action_1, 500/SCHEDULER_INTERVAL, 101) )
    Serial.print("Scheduler error: max number of events reached");
  addSchedulerEvent( action_2, 3000/SCHEDULER_INTERVAL, 102);
  addSchedulerEvent( printSterretjes, 3000/SCHEDULER_INTERVAL, 103);
  addSchedulerEvent( printPlusjes, 10000/SCHEDULER_INTERVAL, 200);
}

void loop()
{
  unsigned long currentMilliSeconds;
 
  //
  // Handle 100ms scheduler check. Deze trigger evt. in ISR
  //
  // Maakt gebruik van de 1ms Arduino counter
  //
  currentMilliSeconds = millis();
  if(currentMilliSeconds - previousMilliSeconds > SCHEDULER_INTERVAL) 
  {
    previousMilliSeconds = currentMilliSeconds; 
    handleScheduler();
  }
}

