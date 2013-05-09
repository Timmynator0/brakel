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
 
  ntp.setup();
  data.day =ntp.getDate();
}


void loop(){
  
  Serial.println("Started");
   
  manager.writeToSD(&data);

  ntp.init();
 
  
  ntp.PrintDateTime();
  Serial.println("Done");
  delay(1000);
  
  

}

