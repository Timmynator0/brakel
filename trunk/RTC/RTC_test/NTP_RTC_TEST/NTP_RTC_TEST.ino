
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include <Wire.h>
#include <RTClib.h>


RTC_DS1307 RTC;
// MAC address for your Ethernet shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x8D, 0x40 };
byte ip[] = { 192, 168, 0, 1 };                      // no DHCP so we set our own IP address
byte subnet[] = { 255, 255, 255, 0 };                // subnet mask
byte gateway[] = { 192, 168, 0, 2 }; 


unsigned int localPort = 8888;      // local port to listen for UDP packets
byte timeServer[]    = {192, 43, 244, 18}; // time.nist.gov

//time_t prevDisplay = 0; // when the digital clock was displayed


//http://playground.arduino.cc/Main/DS1307OfTheLogshieldByMeansOfNTP
//http://support.ntp.org/bin/view/Main/WebHome
EthernetUDP Udp;
const int NTP_PACKET_SIZE= 48;
byte pb[NTP_PACKET_SIZE]; 


void setup(){
  Serial.begin(9600);
  
  if (Ethernet.begin(mac) != 1) {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(15000);
  }else{
    Serial.println("Network Success");
  }
 Udp.begin(localPort);
   
 Wire.begin();
 RTC.begin();
 Serial.println("Start RTC");
  
}


void loop(){
  
  DateTime now = RTC.now();

  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.print(now.second());
  Serial.print(" ");
  Serial.print(now.day());
  Serial.print("/");
  Serial.print(now.month());
  Serial.print("/");
  Serial.println(now.year(), DEC);
  
  
  sendNTPpacket(timeServer);
  delay(1000);
  
  if(Serial.available()){
    if(Serial.read() == '2')
      RTC.adjust(DateTime(2013,04,16,13,54,00));
  }
  
  
  if(Udp.available()){
   Serial.println("UDP available"); 
    
  }else{
    Serial.println("No UDP available");
    
  }
}


// send an NTP request to the time server at the given address 
unsigned long sendNTPpacket(byte *address)
{
  // set all bytes in the buffer to 0
  memset(pb, 0, NTP_PACKET_SIZE); 
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  pb[0] = 0b11100011;   // LI, Version, Mode
  pb[1] = 0;     // Stratum, or type of clock
  pb[2] = 6;     // Polling Interval
  pb[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  pb[12]  = 49; 
  pb[13]  = 0x4E;
  pb[14]  = 49;
  pb[15]  = 52;

 
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(pb,NTP_PACKET_SIZE);
  Udp.endPacket(); 
   

}

