
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#include <Wire.h>
#include <RTClib.h>
#include <Time.h>


RTC_DS1307 RTC;
// MAC address for your Ethernet shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x8D, 0x40 };
byte ip[] = { 192, 168, 0, 1 };                      // no DHCP so we set our own IP address
byte subnet[] = { 255, 255, 255, 0 };                // subnet mask
byte gateway[] = { 192, 168, 0, 2 }; 


unsigned int localPort = 8888;      // local port to listen for UDP packets
IPAddress timeServer(193, 79, 237, 14);
//96, 44, 157, 90);


//time_t prevDisplay = 0; // when the digital clock was displayed


//http://playground.arduino.cc/Main/DS1307OfTheLogshieldByMeansOfNTP
//http://support.ntp.org/bin/view/Main/WebHome
EthernetUDP Udp;
const int NTP_PACKET_SIZE= 48;
byte pb[NTP_PACKET_SIZE]; 


void setup(){
  Serial.begin(9600);
  int DHCP = 0;
  DHCP = Ethernet.begin(mac);
  if(DHCP)
    Serial.println("DHCP Success");

 Udp.begin(localPort);
   
 Wire.begin();
 RTC.begin();
 Serial.println("Start RTC");
  
}


void loop(){
  
  PrintDateTime(RTC.now());

  sendNTPpacket(timeServer);
  delay(1000);
  
  if(Serial.available()){
    if(Serial.read() == '2')
      RTC.adjust(DateTime(2013,04,18,10,54,00));
  }
  
  if(Udp.parsePacket()){
     Serial.println("UDP available"); 
     Udp.read(pb, NTP_PACKET_SIZE);
      unsigned long t1, t2, t3, t4;
    t1 = t2 = t3 = t4 = 0;
    for (int i=0; i< 4; i++)
    {
      t1 = t1 << 8 | pb[16+i];      
      t2 = t2 << 8 | pb[24+i];      
      t3 = t3 << 8 | pb[32+i];      
      t4 = t4 << 8 | pb[40+i];
    }

    // part of the fractional part
    // could be 4 bytes but this is more precise than the 1307 RTC 
    // which has a precision of ONE second
    // in fact one byte is sufficient for 1307 
    float f1,f2,f3,f4;
    f1 = ((long)pb[20] * 256 + pb[21]) / 65536.0;      
    f2 = ((long)pb[28] * 256 + pb[29]) / 65536.0;      
    f3 = ((long)pb[36] * 256 + pb[37]) / 65536.0;      
    f4 = ((long)pb[44] * 256 + pb[45]) / 65536.0;

    // NOTE:
    // one could use the fractional part to set the RTC more precise
    // 1) at the right (calculated) moment to the NEXT second! 
    //    t4++;
    //    delay(1000 - f4*1000);
    //    RTC.adjust(DateTime(t4));
    //    keep in mind that the time in the packet was the time at
    //    the NTP server at sending time so one should take into account
    //    the network latency (try ping!) and the processing of the data
    //    ==> delay (850 - f4*1000);
    // 2) simply use it to round up the second
    //    f > 0.5 => add 1 to the second before adjusting the RTC
    //   (or lower threshold eg 0.4 if one keeps network latency etc in mind)
    // 3) a SW RTC might be more precise, => ardomic clock :)


    // convert NTP to UNIX time, differs seventy years = 2208988800 seconds
    // NTP starts Jan 1, 1900
    // Unix time starts on Jan 1 1970.
    const unsigned long seventyYears = 2208988800UL;
    t1 -= seventyYears;
    t2 -= seventyYears;
    t3 -= seventyYears;
    t4 -= seventyYears;

   
  /*  Serial.println("T1 .. T4 && fractional parts");
    PrintDateTime(DateTime(t1)); Serial.println(f1,4);
    PrintDateTime(DateTime(t2)); Serial.println(f2,4);
    PrintDateTime(DateTime(t3)); Serial.println(f3,4);*/
    
    PrintDateTime(DateTime(t4)); Serial.println(f4,4);
    Serial.println();

    // Adjust timezone and DST... in my case substract 4 hours for Chile Time
    // or work in UTC?
    t4 += (2 * 3600L);     // Notice the L for long calculations!!
    t4 += 1;               // adjust the delay(1000) at begin of loop!
 //   if (f4 > 0.4) t4++;    // adjust fractional part, see above
  //  RTC.adjust(DateTime(t4));
    RTC.adjust(DateTime(t4));

    Serial.print("RTC after : ");
    PrintDateTime(RTC.now());
    Serial.println();

    Serial.println("done ...");
    // endless loop 
    while(1){
     PrintDateTime(RTC.now());
     delay(1000);
     
      if(Serial.available()){
        if(Serial.read() == '2')
          RTC.adjust(DateTime(2013,04,18,10,54,00));
      }
    }
    
  }else{
    Serial.println("No UDP available");
   // delay(60000L); 
  }
}


void PrintDateTime(DateTime t)
{
    char datestr[24];
    sprintf(datestr, "%04d-%02d-%02d  %02d:%02d:%02d  ", t.year(), t.month(), t.day(), t.hour(), t.minute(), t.second());
    Serial.println(datestr);  
}


// send an NTP request to the time server at the given address 
unsigned long sendNTPpacket(IPAddress& address)
{
  memset(pb, 0, NTP_PACKET_SIZE);
  pb[0] = 0b11100011;
  pb[1] = 0;
  pb[2] = 6;
  pb[3] = 0xEC;
  pb[12]  = 49;
  pb[13]  = 0x4E;
  pb[14]  = 49;
  pb[15]  = 52;                  
  Udp.beginPacket(address, 123);
  Udp.write(pb,NTP_PACKET_SIZE);
  Udp.endPacket();
}



/** Test !!!!! */

///* ******** Ethernet Card Settings ******** */
//// Set this to your Ethernet Card Mac Address
//byte mac[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
// 
///* ******** NTP Server Settings ******** */
///* us.pool.ntp.org NTP server
//   (Set to your time server of choice) */
//   //96, 44, 157, 90
//IPAddress timeServer(195,240,184,156);
// 
///* Set this to the offset (in seconds) to your local time
//   This example is GMT - 6 */
//const long timeZoneOffset = -21600L;  
// 
///* Syncs to NTP server every 15 seconds for testing,
//   set to 1 hour or more to be reasonable */
//unsigned int ntpSyncTime = 15;        
// 
// 
///* ALTER THESE VARIABLES AT YOUR OWN RISK */
//// local port to listen for UDP packets
//unsigned int localPort = 8888;
//// NTP time stamp is in the first 48 bytes of the message
//const int NTP_PACKET_SIZE= 48;      
//// Buffer to hold incoming and outgoing packets
//byte packetBuffer[NTP_PACKET_SIZE];  
//// A UDP instance to let us send and receive packets over UDP
//EthernetUDP Udp;                    
//// Keeps track of how long ago we updated the NTP server
//unsigned long ntpLastUpdate = 0;    
//// Check last time clock displayed (Not in Production)
//int prevDisplay = 0;            
// 
//void setup() {
//   Serial.begin(9600);
//   
//   // Ethernet shield and NTP setup
//   int i = 0;
//   int DHCP = 0;
//   DHCP = Ethernet.begin(mac);
//   //Try to get dhcp settings 30 times before giving up
//   while( DHCP == 0 && i < 30){
//     delay(1000);
//     DHCP = Ethernet.begin(mac);
//     i++;
//   }
//   if(!DHCP){
//    Serial.println("DHCP FAILED");
//     for(;;); //Infinite loop because DHCP Failed
//   }
//   Serial.println("DHCP Success");
//   
//   //Try to get the date and time
//   int trys=0;
//   while(!getTimeAndDate() && trys<10) {
//     trys++;
//   }
//}
// 
//// Do not alter this function, it is used by the system
//int getTimeAndDate() {
//   int flag=0;
//   Udp.begin(localPort);
//   sendNTPpacket(timeServer);
//   delay(1000);
//   if (Udp.parsePacket()){
//     Serial.println("YES");
//     Udp.read(packetBuffer,NTP_PACKET_SIZE);  // read the packet into the buffer
//     unsigned long highWord, lowWord, epoch;
//     highWord = word(packetBuffer[40], packetBuffer[41]);
//     lowWord = word(packetBuffer[42], packetBuffer[43]);  
//     epoch = highWord << 16 | lowWord;
//     epoch = epoch - 2208988800 + timeZoneOffset;
//     flag=1;
//    // setTime(epoch);
//   //  ntpLastUpdate = now();
//   }
//   return flag;
//}
// 
//// Do not alter this function, it is used by the system
//unsigned long sendNTPpacket(IPAddress& address)
//{
//  memset(packetBuffer, 0, NTP_PACKET_SIZE);
//  packetBuffer[0] = 0b11100011;
//  packetBuffer[1] = 0;
//  packetBuffer[2] = 6;
//  packetBuffer[3] = 0xEC;
//  packetBuffer[12]  = 49;
//  packetBuffer[13]  = 0x4E;
//  packetBuffer[14]  = 49;
//  packetBuffer[15]  = 52;                  
//  Udp.beginPacket(address, 123);
//  Udp.write(packetBuffer,NTP_PACKET_SIZE);
//  Udp.endPacket();
//}
// 
//// Clock display of the time and date (Basic)
//void clockDisplay(){
// /* Serial.print(hour());
//  printDigits(minute());
//  printDigits(second());
//  Serial.print(" ");
//  Serial.print(day());
//  Serial.print(" ");
//  Serial.print(month());
//  Serial.print(" ");
//  Serial.print(year());
//  Serial.println();*/
//}
// 
//// Utility function for clock display: prints preceding colon and leading 0
//void printDigits(int digits){
//  Serial.print(":");
//  if(digits < 10)
//    Serial.print('0');
//  Serial.print(digits);
//}
// 
//// This is where all the magic happens...
//void loop() {
//    // Update the time via NTP server as often as the time you set at the top
//    //if(now()-ntpLastUpdate > ntpSyncTime) {
//      int trys=0;
//      while(!getTimeAndDate() && trys<10){
//        trys++;
//      //}
//      if(trys<10){
//        Serial.println("ntp server update success");
//      }
//      else{
//        Serial.println("ntp server update failed");
//      }
//    }
//   
//    // Display the time if it has changed by more than a second.
//  //  if( now() != prevDisplay){
//   //   prevDisplay = now();
//      clockDisplay();  
//   // }
//
//
//}
