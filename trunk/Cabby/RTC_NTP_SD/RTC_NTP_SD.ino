#include <SPI.h>
#include <RTClib.h>
#include <Types.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Wire.h>
#include <SDManager.h>
#include <Buffer.h>
#include <BufferManager.h>

NTP ntp;
SDManager manager;

xbee_data data;

void setup(){
  Serial.begin(9600);
   Serial.println(manager.initSD());
  
  delay(1000);
 
  if(ntp.setup())
    Serial.println("Inet succes");
  
  manager.setNTP(ntp);
  
  if(ntp.sendRequest())
      Serial.println("Time Updated");
}

void loop(){

   data.timeStamp = ntp.GetDateTime();
   data.lightIntensity = 12;
   manager.storeToBuffer(data);
   manager.readFromBuffer();

  ntp.PrintDateTime();
  
  Serial.println("Done ");
  Serial.println();
  
  delay(10* 1000);
  
  
//
//  Serial.println("Data is : ");
//  xbee_data* d;
//   d = manager.getData();
//   
//   for(int i = 0; i < manager.getDataSize();i++){
//    Serial.println(d[i].temperature);
//  
//   }
//    delay(60L * 1000L);

}




void serialEvent() 
{
  while (Serial.available()) 
  {
    char ch = (char)Serial.read();
    if( ch >= '0' && ch <= '9' )
    {
      xbee_data data2 = {
        0,int(ch),12,0,0,0,0      };
      manager.storeToBuffer(data2);
       
    }
  }
}

