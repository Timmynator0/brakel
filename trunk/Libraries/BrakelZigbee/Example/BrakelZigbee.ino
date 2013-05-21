/*
    Serial Event: Read XBee IO-Packet
 
   When new serial data (an XBee IO-packet) arrives, this sketch adds it to an array of bytes ('packet').
   At the end of the packet:
   - the 64-bits network address is parsed,
   - the values of the temparature, the humudity and the light intensity are converted in int's
   - these values are displayed (--> later: these values are stored in the buffer)
 
   SerialEvent occurs whenever a new data comes in the hardware serial RX.  
   This routine is run between each time loop() runs, so using delay inside loop can delay response.  
   Multiple bytes of data may be available in the serial port.
   
   The XBee-device is conneted to serial port 3 of the Arduino Mega
   the monitor is connected to default Serial Port (port number 0)

   8 mei 2013, AJW, Avans HS, Technische Informatica
 */
#include <Arduino.h>
//#include <RTClib.h>
#include <Types.h>
#include <BrakelZigbee.h>
  
void setup() {
    // initialize serial;
    Serial.begin(9600);
    Serial3.begin(9600);
}

void loop() {
    // do something small
    delay(1);    
}

// Display the 64-bits network address and 
//  the 10-bits value of temperature, humidity and light intensity of the latest packet
//
void showData() {
   /*Serial.print("Addres: "); 
   for (int i=0; i<8; i++) {
      Serial.print(zigbeeAddress64[i],HEX); Serial.print(' '); 
   }*/
   Serial.println();
   Serial.print("T="); Serial.print(zigbeeData.temperature);
   Serial.print("     H="); Serial.print(zigbeeData.humidity);
   Serial.print("     I="); Serial.println(zigbeeData.lightIntensity);
   Serial.println();
}

/*
  SerialEvent occurs whenever a new data of an XBee-package comes in the hardware serial RX. 
  This routine is run between each time loop() runs, so using delay inside loop can delay response.  
  Multiple bytes of data may be available.
  serialEvent3: 
*/
void serialEvent3() {
  zigbeeParsePacket();
}

