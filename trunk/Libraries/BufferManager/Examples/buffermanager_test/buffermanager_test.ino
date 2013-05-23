#include <Ethernet.h>
#include <EthernetUDP.h>
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <Types.h>
#include <Buffer.h>
#include <BufferManager.h>

#define SDCARD  0
#define DATABASE 1

BufferManager manager;
void setup()
{
  Serial.begin(9600);
}

xbee_data getal;

void loop()
{
  manager.showBuffer(); 
  if( false == manager.read(&getal,SDCARD) )
  {
    Serial.println("buffer empty");
  }
  else
  {
    Serial.print("temperature = "); 
    Serial.println(getal.temperature);
  }
  if( false == manager.read(&getal,DATABASE) )
  {
    Serial.println("buffer empty");
  }
  else
  {
    Serial.print("lightIntensity = "); 
    Serial.println(getal.lightIntensity);
  }
  delay(500);
}
// Voeg data tot aan buffer, fast!
void serialEvent() 
{
  while (Serial.available()) 
  {
    char ch = (char)Serial.read();
    if( ch >= '0' && ch <= '9' )
    {
      xbee_data data = {
        0,int(ch),12,0,0,0,0      };

      if(!manager.store(data))
        Serial.println("Storing data Failed due to buffer overflow!");
    }
  }
}





