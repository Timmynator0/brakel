#include <BrakelZigbee.h>
#include <Buffer.h>
#include <BufferManager.h>
#include <RTClib.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <string.h>
#include <Types.h>
#include <Wire.h>
#include <Scheduler.h>
#include <Timers.h>
#include <SDManager.h>
#include <SD.h>
#include <String.h>
#include <LCD.h>
#include <MemoryFree.h>
#include <DBClient.h>
#define SD_INTERVAL 100

NTP ntp;
BufferManager bufferManager;
BrakelZigbee bxbee;
DBClient dbClient;
SDManager sdManager;
bool debug = true;
EthernetClient client2; 

void loop()
{
  
}

void SchedulerHandler(void)
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

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

void setup()
{

  boolean retVal = true;
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial.println(sdManager.initSD());
  Serial.println("Fetching IP through DHCP");
  while (Ethernet.begin(mac) == 0) 
  {
    Serial.println("Failed to fetch an IP, trying again in 2 seconds");
    // try again after 2seconds
    delay(2000);
  }
  Serial.println("Fetched IP!");
  sdManager.setBufferManager(&bufferManager);
  dbClient.setBufferManager(&bufferManager);
  dbClient.setEthernetClient(&client2);

  if(ntp.setup())
  {
    Serial.println("NTP done" );
    bxbee.setNTP(&ntp);
  }
Timers1.initialize(10, 1);//10 milliseconden wachten om samen met het interval van de sheduler van 100 ms het interval op 1 seonde te leggen.
  Timers1.attachInterruptTimer1(SchedulerHandler);
  initScheduler();

  //sdEvent
  addSchedulerEvent(sdHandler, 3, 1); //Interval van 1 seconde en ID van 1. 

  //ntpEvent
  addSchedulerEvent(ntpHandler, 86400, 2); //Interval van 1 dag en ID van 2. 

  //dbEvent
  addSchedulerEvent(transmitDb, 30, 3); //Interval van 1 seconde en ID van 1.

  //lcdEvent
  //  addSchedulerEvent(lcdHandler, 2, 3); //Intervan van 1 seconde en ID van 3. 

  

  //todo: Handler voor als er geen NTP verbinding was.


  //     if(retVal)
  //      {
  //        LCDMessage message = {"Setup succesvol.", "", SCREEN_MESSAGE, 0};
  //        LCDAddMessage(message);
  //      }
  Serial.println("setup done");
}

void serialEvent3() {
  if(zigbeeParsePacket())
  {
    if(!bufferManager.store(zigbeeData))
    {
      Serial.println("f");
    }
    else
    {
      Serial.println("s");
    }
  }
}

void sdHandler(void)
{
  Serial.print("freememory: ");
  Serial.println(freeMemory());
  sdManager.readFromBuffer();
}

void transmitDb(void)
{ 
  schedulerLock = true;
  dbClient.dbClientSend();
  schedulerLock = false;
}

void ntpHandler(void)
{
  ntp.sendRequest();
}

void lcdHandler(void)
{
  LCDUpdate();
}






