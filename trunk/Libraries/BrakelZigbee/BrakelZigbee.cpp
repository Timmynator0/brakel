//#ifndef _BrakelZigbee_CPP_
//#define _BrakelZigbee_CPP_

#ifndef _BrakelZigbee_h_
#include <BrakelZigbee.h>
#endif



byte zigbeePacket[30];                  // an array to hold incoming data
byte zigbeeAddress64[8];                // array for the 64-bits network address
int  zigbeePacketIndex = 0;             // pointer in zigbeePacket array
int  zigbeeAddressIndex = 0;            // pointer in zigbeeAddress64 array

byte inByte;                      // read byte
int  zigbeePacketLength;                // read value of zigbeePacket length
byte  zigbeePacketID;                   // read value of zigbeePacket ID (for IO zigbeePacket: ID = $92)

boolean newZigbeePacket = FALSE;        // indicator for a new zigbeePacket (after the start delimiter 7E)
boolean zigbeePacketOK = FALSE;         // induactor for a valid zigbeePacket (the checksum is OK)
byte checksum = 0;                // calculated checksum
// recieved 10-bit values for the temperature, the humidity and the light intensity

xbee_data zigbeeData;

bool zigbeeParsePacket();
NTP *rtc;


//function used for decryption of a zigbee packet. 
bool zigbeeParsePacket() {
  if(!Serial3.available())
  {return false;}
  while (Serial3.available()) {                              // Is a byte present?

    inByte = (char)Serial3.read();                           // Get the new byte:
        
    if (inByte == STARTDELIMITER) {                         // A new zigbeePacket arrives
        zigbeePacketIndex = 0;
        zigbeeAddressIndex = 0;
        newZigbeePacket = TRUE;
        checksum = 0;
    } 
    
    if (newZigbeePacket) {
        zigbeePacket[zigbeePacketIndex] = inByte;                          // store the byte in the array
        // for testing: 
        //Serial3.print(zigbeePacketIndex); Serial3.print(":"); Serial3.println(zigbeePacket[zigbeePacketIndex], HEX);
        if (zigbeePacketIndex == 2) { 		// read zigbeePacket length
            zigbeePacketLength = inByte+4;                          // the read value is the #bytes 
                                                              //    between the length and the checksum
                                                              //    the total length is 4 bytes more
        }
        if (zigbeePacketIndex == 3) {                                // read zigbeePacket ID: is it an IO package?
            newZigbeePacket =  inByte == IO_DATA_ID ;                // if not: break
            checksum +=  inByte;
        }
        
        // read the rest of the zigbeePacket, except the last one, calculate the checksum
        if ((zigbeePacketIndex > 3) && (zigbeePacketIndex <= zigbeePacketLength -2)) {
            checksum +=  inByte;
        }
        // read the last byte, the checksum, and validate
        // check that byte 18 (analog channel mask) == 0000 1110 (0x0E): IO lines 1,2,3 are AD-values
        // FUTURE: perhaps a different channell mask because of a CO@-sensor
        // if OK: store (display) the 64-bits address and the measured values
        if ((zigbeePacketIndex > 3) && (zigbeePacketIndex == zigbeePacketLength -1) ) {
            newZigbeePacket = FALSE;
            checksum = 0xFF - checksum;
            // validate checksum and analog channel mask
            if ((checksum == inByte) && (zigbeePacket[18] == ANALOG_CHANNEL_MASK))  {
                // the zigbeePacket is valid
                for (zigbeeAddressIndex = 0; zigbeeAddressIndex < 8; zigbeeAddressIndex++) {
                  zigbeeAddress64[zigbeeAddressIndex] = zigbeePacket[4 + zigbeeAddressIndex];
                }
                zigbeeData.temperature = 256*zigbeePacket[19] + zigbeePacket[20];
                zigbeeData.humidity = 256*zigbeePacket[21] + zigbeePacket[22];
                zigbeeData.lightIntensity = 256*zigbeePacket[23] + zigbeePacket[24];
				zigbeeData.timeStamp = rtc->GetDateTime();
				
				zigbeeData.CO2 = -1;
				
				//add zigbee Adress
				zigbeeData.nodeAddrLow = ((unsigned long)zigbeeAddress64[0])<<24;
				zigbeeData.nodeAddrLow |= ((unsigned long)zigbeeAddress64[1])<<16;
				zigbeeData.nodeAddrLow |= ((unsigned long)zigbeeAddress64[2])<<8;
				zigbeeData.nodeAddrLow |= ((unsigned long)zigbeeAddress64[3]);
				
				zigbeeData.nodeAddrHigh = ((unsigned long)zigbeeAddress64[4])<<24;
				zigbeeData.nodeAddrHigh |= ((unsigned long)zigbeeAddress64[5])<<16;
				zigbeeData.nodeAddrHigh |= ((unsigned long)zigbeeAddress64[6])<<8;
				zigbeeData.nodeAddrHigh |= ((unsigned long)zigbeeAddress64[7]);
				
				/*
                Serial.println(zigbeeData.nodeAddrHigh,HEX);
                Serial.println(zigbeeData.nodeAddrLow,HEX);*/
				return true;
             }
            // if zigbeePacket is not valid: do nothing
            else {
				return false;
            }
      }
      // next byte of the package
      zigbeePacketIndex ++;
    } 
  }
  return false;
}

void BrakelZigbee::setNTP(NTP *rtc)
{
	rtc = rtc;
}
//#endif _BrakelZigbee_CPP_