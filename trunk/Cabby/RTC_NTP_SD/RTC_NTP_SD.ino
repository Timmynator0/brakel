#include <SPI.h>
#include <RTClib.h>

#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Wire.h>
#include <SDManager.h>

NTP ntp;

SDManager manager;


xbee_data data;

void setup(){
  Serial.begin(9600);
   manager.initSD();
  
  delay(1000);
  
  ntp.setup();
  
}

void loop(){
  
   Serial.println("Started");
   ntp.init();
   data.timeStamp = ntp.GetDateTime();
   data.temperature = 1;
   data.lightIntensity = 2;
   data.CO2 = 3;
   data.humidity = 4;
   data.nodeAddrLow = 5;
   data.nodeAddrHigh = 6;
   
   //manager.removeFile("17052013.txt");
//   manager.writeToSD(&data);
//   Serial.println("Done Writing......");
  
 // ntp.PrintDateTime();
  Serial.println("Start Reading......");
//  delay(1000);
//  
  manager.readFromSD(&data,"19052013.txt");
  Serial.println("Done Reading......");
////  Serial.println(data.humidity);

  Serial.println("Data is : ");
  xbee_data* d;
   d = manager.getData();
   
   for(int i = 0; i < manager.getDataSize();i++){
    Serial.println(d[i].temperature);
  
   }
    delay(60L * 1000L);

}

