//zigbee code
#ifndef _BrakelZigbee_h_
#define _BrakelZigbee_h_
#include <BrakelZigbee.h> 
/*

	*****************************IMPORTANT*****************************
	*Make sure the pins are connected to Serial3 in stead of Serial1. *
	*******************************************************************

    Serial Event: Read XBee IO-zigbeePacket
 
   When new serial data (an XBee IO-zigbeePacket) arrives, this sketch adds it to an array of bytes ('zigbeePacket').
   At the end of the zigbeePacket:
   - the 64-bits network address is parsed,
   - the values of the temparature, the humudity and the light intensity are converted in int's
   - these values are saved
 
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
 
#define STARTDELIMITER       0x7E    // the value of the start byte of a xbee zigbeePacket
#define ANALOG_CHANNEL_MASK  0x0E    //
#define IO_DATA_ID           0x92;   // the ID value of a IO data zigbeePacket
#define TRUE   1
#define FALSE  0

extern byte zigbeePacket[30];                  // an array to hold incoming data
extern byte zigbeeAddress64[8];                // array for the 64-bits network address
extern int  zigbeePacketIndex;             // pointer in zigbeePacket array
extern int  zigbeeAddressIndex;            // pointer in zigbeeAddress64 array

extern byte inByte;                      // read byte
extern int  zigbeePacketLength;                // read value of zigbeePacket length
extern byte  zigbeePacketID;                   // read value of zigbeePacket ID (for IO zigbeePacket: ID = $92)

extern boolean newZigbeePacket;        // indicator for a new zigbeePacket (after the start delimiter 7E)
extern boolean zigbeePacketOK;         // induactor for a valid zigbeePacket (the checksum is OK)
extern byte checksum;                // calculated checksum
// recieved 10-bit values for the temperature, the humidity and the light intensity

extern xbee_data zigbeeData;

extern bool zigbeeParsePacket();
#endif