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
const String savingFailed = "Saving Failed";
const String savingSucces = "Saving Succes";

void loop()
{
  
  
  for(int i = 0 ; i < 100 ; i++);
  {
   delay(1); 
  }
   
   while(client2.available()) 
   {
    char c = client2.read();
    //Serial.print(c);

    }


    //dbClient.getResponse();
 
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


  while (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    delay(1000);
  }
  sdManager.setBufferManager(&bufferManager);
  dbClient.setBufferManager(&bufferManager);
  dbClient.setEthernetClient(&client2);
 
 
  // dbClient.dbClientSend(); 
 
  //noInterrupts();
//  Serial.println("getting ip");
  //  while (Ethernet.begin(mac) != 1)
  //  {
  //    Serial.println("Error getting IP address via DHCP, trying again...");
  //    delay(15000);
  //  }
 // if(ntp.setup())
  {
//    Serial.println("NTP done" );
    
   // sdManager.setNTP(&ntp); 
//    bxbee.setNTP(&ntp);
//  }
 


  initScheduler();
  
  //sdEvent
  addSchedulerEvent(sdHandler, 20, 1); //Interval van 1 seconde en ID van 1. 
  //tnpEvent
  addSchedulerEvent(ntpHandler, 86400, 2); //Interval van 1 dag en ID van 2. 
  addSchedulerEvent(transmitDb, 100, 3); //Interval van 1 seconde en ID van 1.
  //lcdEvent
  //  addSchedulerEvent(lcdHandler, 2, 3); //Intervan van 1 seconde en ID van 3. 
  Timers1.initialize(10, 1);//10 milliseconden wachten om samen met het interval van de sheduler van 100 ms het interval op 1 seonde te leggen.
  Timers1.attachInterruptTimer1(SchedulerHandler);
  //todo: Handler voor als er geen NTP verbinding was.


  //     if(retVal)
  //      {
  //        LCDMessage message = {"Setup succesvol.", "", SCREEN_MESSAGE, 0};
  //        LCDAddMessage(message);
  //      }
  //interrupts();
  Serial.println("setup done");
}
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
  //Serial.print("timertick");
    Serial.println(freeMemory());
    
    //xbee_data datading;
    //bufferManager.read(&datading, DATABASE);
    //bufferManager.read(&datading, SDCARD);
    sdManager.readFromBuffer();
    
}

void transmitDb(void)
{ 
    dbClient.dbClientSend();
}

void ntpHandler(void)
{
  ntp.sendRequest();
}

void lcdHandler(void)
{
  LCDUpdate();
}




