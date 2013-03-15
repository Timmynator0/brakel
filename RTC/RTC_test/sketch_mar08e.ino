
#include <Rtc.h>
#include <Wire.h>


int command;
Rtc rtc(10);

void setup(){
  rtc.init();
  Serial.begin(9600);
 
}


void loop(){
  rtc.getTimeDate();
  Serial.print(rtc.getHour());
  Serial.print(":");
  Serial.print(rtc.getMinutes());
  Serial.print(":");
  Serial.print(rtc.getSecond());
  Serial.print(" ");
  Serial.print(rtc.getDayOfMonth());
  Serial.print("/");
  Serial.print(rtc.getMonth());
  Serial.print("/");
  Serial.println(rtc.getYear());
  delay(1000);
  
  if(Serial.available()){
    command = Serial.read();
    if(command == 50){
      rtc.setTimeDay(0,22,15,11,8,03,13);
    }
  }
}
