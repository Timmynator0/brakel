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

#define SD_INTERVAL 100

NTP ntp;
BufferManager bufferManager;
SDManager sdManager;
bool debug = true;


const String savingFailed = "Saving Failed";
const String savingSucces = "Saving Succcccccccccccces";

void loop()
{}

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

void setup()
{
    boolean retVal = true;
    Serial.begin(9600);
    Serial3.begin(9600);
        
    //ntp.setup();  
    Serial.println("tadaa koekjes");
    //ntp.sendRequest();
    
    sdManager.initSD();
    sdManager.setBufferManager(&bufferManager);
    
    initScheduler();
    //sdEvent
    addSchedulerEvent(sdHandler, 1, 1); //Interval van 1 seconde en ID van 1. 
    //tnpEvent
    addSchedulerEvent(ntpHandler, 86400, 2); //Interval van 1 dag en ID van 2. 
    //lcdEvent
    addSchedulerEvent(lcdHandler, 1, 3); //Intervan van 1 seconde en ID van 3. 
    Timers1.initialize(10, 1);//10 milliseconden wachten om samen met het interval van de sheduler van 100 ms het interval op 1 seonde te leggen.
    Timers1.attachInterruptTimer1(SchedulerHandler);
    //todo: Handler voor als er geen NTP verbinding was.
    
    
    if(retVal)
    {
      LCDMessage message = {"Setup succesvol.", "", SCREEN_MESSAGE, 0};
      LCDAddMessage(message);
    }
}

void serialEvent3() {
  if(zigbeeParsePacket())
  {
    if(!bufferManager.store(zigbeeData))
    {
        Serial.println(savingFailed);
    }
    else
    {
        Serial.println(savingSucces);
    }
  sdManager.readFromBuffer();
    xbee_data datading;
    bufferManager.read(&datading, DATABASE);
  }
}

void sdHandler(void)
{
  sdManager.readFromBuffer();
}

void ntpHandler(void)
{
  ntp.sendRequest();
}

void lcdHandler(void)
{
  LCDUpdate();
}
