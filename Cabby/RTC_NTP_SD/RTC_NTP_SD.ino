#include <SPI.h>
#include <RTClib.h>

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Wire.h>
#include <SDManager.h>

NTP ntp;

SDManager manager;

xbee_data data;
char *test;
void setup(){
  Serial.begin(9600);
  manager.initSD();
  delay(1000);
  ntp.setup();
  data.timeStamp = ntp.GetDateTime();
}

void loop(){
  
  Serial.println("Started");
   
  manager.writeToSD(&data);
  Serial.println("Done Writing......");
//  ntp.init();
 
  
//  ntp.PrintDateTime();
  Serial.println("Start Reading......");
  delay(1000);
  
  manager.readFromSD();
   Serial.println("Done Reading......");
  delay(60L * 1000L);

}

