
#include <SPI.h>
#include <RTClib.h>

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SD.h>
#include <Wire.h>

NTP ntp;

void setup(){
  Serial.begin(9600);
  ntp.setup();
  SD.begin(4);
}


void loop(){
  
  Serial.println("Started");

  ntp.init();
  ntp.PrintDateTime();
  Serial.println("Done");
  delay(1000);

}
