#include <Wire.h>


int clockAddress = 0x68;
int command = 0;
long previousMillis = 0;
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
byte test;
bool check = false;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  
}

void loop(){
  if(check == false){
    check= true;
    setTimeDate(20,03,22);
  }else{
    getDate();
  }
  int command;
  if(Serial.available()){
    command = Serial.read();
    Serial.println(command);
  }
}

void setTimeDate(int seconds, int minutes, int hours){
  Wire.beginTransmission(clockAddress);
  Wire.write(byte(0x00));
  Wire.write(decToBcd(seconds));
  Wire.write(decToBcd(minutes));
  Wire.write(decToBcd(hours));
  
  Wire.write(decToBcd(11));
  Wire.write(decToBcd(06));
  Wire.write(decToBcd(03));
  Wire.write(decToBcd(13));
  
  
  Wire.endTransmission();
}




void getDate(){
  
  Wire.beginTransmission(clockAddress);
  Wire.write(byte(0x00));
  Wire.endTransmission();
  Wire.requestFrom(clockAddress, 7);
  
  second = bcdToDec(Wire.read() & 0x7f);
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read() & 0x3f);
  
  dayOfWeek = bcdToDec(Wire.read());
  dayOfMonth = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.print(second, DEC);
  Serial.print(" ");
  
  Serial.print(dayOfMonth);
  Serial.print("/");
  Serial.print(month);
  Serial.print("/");
  Serial.println(year);
  delay(1000);
}

byte decToBcd(byte val){
 return ((val/10*16) + (val%10)); 
}

byte bcdToDec(byte val){
  return ((val/16*10) + (val%16));
  
}
