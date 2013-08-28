#define DB //comment to disable DATABASE
#define SDC //comment to disable SDCARD
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
#ifdef SDC
#include <SDManager.h>
#include <SD.h>
#endif
#include <String.h>
//#include <LCD.h> //error?
#include <MemoryFree.h>
#ifdef DB
#include <DBClient.h>
#endif
#define SD_INTERVAL 100



NTP ntp;
BufferManager bufferManager;
BrakelZigbee bxbee;
#ifdef SDC
SDManager sdManager;
#endif
#ifdef DB
DBClient dbClient;
bool noNTP = true;
EthernetClient client2; 
#endif

bool debug = true;


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
  
  RTC_DS1307 RTC2;

void setup()
{
  
  boolean retVal = true;
  Serial.begin(9600);
  Serial3.begin(9600);
  #ifdef SDC
  Serial.println(sdManager.initSD());
  #endif
  Serial.println("Fetching IP through DHCP");
  while (Ethernet.begin(mac) == 0) 
  {
    Serial.println("Failed to fetch an IP, trying again in 2 seconds");
    // try again after 2-seconds
    delay(2000);
  }
  RTC2.begin();
  Serial.println("Fetched IP!");
  #ifdef SDC
  sdManager.setBufferManager(&bufferManager);
  #endif
  #ifdef DB
  dbClient.setBufferManager(&bufferManager);
    dbClient.setEthernetClient(&client2);
  #endif

  if(ntp.setup())
  {
    RTC2.adjust(ntp.t);
 //   Serial.println(ntp.t.day());
 //   Serial.println("NTP done" );
    bxbee.setNTP(&ntp);
   // noNTP = false;
  }
Timers1.initialize(10, 1);//10 milliseconden wachten om samen met het interval van de sheduler van 100 ms het interval op 1 seonde te leggen.
  Timers1.attachInterruptTimer1(SchedulerHandler);
  initScheduler();
#ifdef SDC
  //sdEvent
  addSchedulerEvent(sdHandler, 3, 1); //Interval van 1 seconde en ID van 1. 
#endif
  //ntpEvent
//  addSchedulerEvent(ntpHandler, 200, 2); //Interval van 1 dag en ID van 2. //86400

  //dbEvent
 #ifdef DB
 addSchedulerEvent(transmitDb, 30, 3); //Interval van 1 seconde en ID van 1.
 #endif

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

void serialEvent3() 
{
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
   #ifndef SDC
   xbee_data tempdata;
   bufferManager.read(&tempdata,SDCARD);
   #endif
   #ifndef DB
   xbee_data tempdata;
   bufferManager.read(&tempdata,DATABASE);
   #endif
}
#ifdef SDC
void sdHandler(void)
{
//  Serial.print("freememory: ");
//  Serial.println(freeMemory());
  sdManager.readFromBuffer();
}
#endif
#ifdef DB
void transmitDb(void)
{ 
  schedulerLock = true;
  dbClient.dbClientSend();
  schedulerLock = false;
  
// if(noNTP)
// { 

// }
 

}
#endif
void ntpHandler(void)
{
    schedulerLock = true;
  Serial.println("NTP HANDLER");
//    if(ntp.setup()) 
//  { 
//    removeSchedulerEvent(4); 
//    bxbee.setNTP(&ntp); 
//  } 
 ntp.sendRequest();
 // RTC2.adjust(ntp.t);

    schedulerLock = false;
// 
}

void lcdHandler(void)
{
 // LCDUpdate();
}






