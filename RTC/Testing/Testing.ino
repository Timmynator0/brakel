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

 
  ntp.setup();
  delay(1000);
  manager.initSD();
  data.day =ntp.getDateSD();
}

void loop(){
  
  Serial.println("Started");
   
  manager.writeToSD(&data);

  ntp.init();
 
  
  ntp.PrintDateTime();
  Serial.println("Done");
  delay(1000);
  
  

}

