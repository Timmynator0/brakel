
#include <SPI.h>
#include <RTClib.h>

#include <Ethernet.h>
#include <EthernetUdp.h>

#include <Wire.h>

NTP ntp;

void setup(){
  Serial.begin(9600);
  
  
}


void loop(){
  
  Serial.println("Started");

  ntp.init();
  Serial.println("Done");
  delay(1000);

}
