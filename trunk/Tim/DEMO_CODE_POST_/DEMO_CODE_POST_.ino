#include <SPI.h>
#include <Ethernet.h>
#include <DBClient.h>
#include <Types.h>
#include <BufferManager.h>
//#include <BrakelZigbee.h>
#include <Buffer.h>
#include <RTClib.h>
#include <EthernetUdp.h>
#include <string.h>
#include <Wire.h>
#include <Scheduler.h>
//#include <Timers.h>
//#include <SDManager.h>
#include <SD.h>
#include <String.h>

//#include <LCD.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client2;
BufferManager bufferManagerInstance;
DBClient dbclient ;
RTC_DS1307 rtc;

void fillbuffer()
{
  int count2 =0;
  while(count2 <= 25)
  {
     xbee_data buffstore = { rtc.now() , 2324,1233 ,12345,76542, 2324, count2 };
    bufferManagerInstance.store(buffstore);
     count2++;
     
    // Serial.println(count2);
  }
}


void setup() 
{
   // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("start");
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // give the Ethernet shield a second to initialize:
  //delay(1000);
  


  Serial.println("starting transmit");
 dbclient.setBufferManager(&bufferManagerInstance);
 dbclient.setEthernetClient(&client2);

 
 dbclient.dbClientSend();
  

  

}

void loop()
{
    
  while(client2.available()) {
    char c = client2.read();
    Serial.print(c);


  }


  // if the server's disconnected, stop the client:
  if (!client2.connected()) {
    Serial.println();
    Serial.println("disconnecting.");


    client2.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }
}
