#include <SPI.h>
#include <Ethernet.h>
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
#include <SDManager.h>
#include <SD.h>
#include <String.h>
//#include <LCD.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(145,48,6,30);

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
BufferManager buffermanagerInstance;



String buildString()
{
  int count = 0;
  const char datapointStart[] PROGMEM= "<XbeeData>\n";
  const char timeStart[] PROGMEM = "\t<Time>";
  const char timeEnd[] PROGMEM = "</Time>\n";
  const char temperatureStart[] PROGMEM ="\t<Temperature>";
  const char temperatureEnd[] PROGMEM = "</Temperature>\n";
  const char CO2Start[] PROGMEM ="\t<CO2>";
  const char CO2End[] PROGMEM = "</CO2>\n";
  const char humidityStart[] PROGMEM ="\t<Humidity>";
  const char humidityEnd[] PROGMEM ="</Humidity>\n";
  const char lightStart[] PROGMEM ="\t<Light>";
  const char lightEnd[] PROGMEM = "</Light>\n";
  const char NodeAdressLowStart[] PROGMEM ="\t<NodeAdressLow>";
  const char NodeAdressLowEnd[] PROGMEM = "</NodeAdressLow>\n";
  const char NodeAdressHighStart[] PROGMEM ="\t<NodeAdressHigh>";
  const char NodeAdressHighEnd[] PROGMEM = "</NodeAdressHigh>\n";
  const char datapointEnd[] PROGMEM ="</XbeeData>\n";
  const char xmlStart[] PROGMEM = "<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\"> <soap:Body>    <storedata xmlns=\"localhost/Receive/\">      <XbeeDataPoints>";
  const char xmlEnd[] PROGMEM = " </XbeeDataPoints> </storedata> </soap:Body></soap:Envelope>";

RTC_DS1307 rtc;
int count2 =0;
  while(count2 <= 25)
  {
     xbee_data buffstore = { rtc.now() , 2324,1233 ,12345,76542, 2324, count2 };
     Serial.println(buffermanagerInstance.store(buffstore));
     count2++;
     
    // Serial.println(count2);
  }
 
String dataString = xmlStart;
 xbee_data data;
 while(count <60)
  {
    
   
   
    buffermanagerInstance.read(&data, DATABASE);
    String datapoint = datapointStart + timeStart + data.timeStamp.unixtime() + timeEnd + temperatureStart + data.temperature + temperatureEnd + CO2Start + data.CO2 +  CO2End + humidityStart + data.humidity + humidityEnd +  lightStart + data.lightIntensity + lightEnd + NodeAdressLowStart + data.nodeAddrLow + NodeAdressLowEnd + NodeAdressHighStart + data.nodeAddrHigh + NodeAdressHighEnd + datapointEnd;
    dataString += datapoint;
    
    count++;    
    
  }

  dataString += xmlEnd;
 


 // Serial.println(dataString);
  return dataString;
}








void setup() {
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
  delay(1000);
  Serial.println(Ethernet.localIP());
  Serial.println("connecting...");
  //////

  String content = buildString();

Serial.println(content);
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // print the HTTP request:



    client.print("POST /Receive/WebService.asmx HTTP/1.1 \r\n");
    client.print("User-Agent: curl/7.24.0 (x86_64-apple-darwin12.0) libcurl/7.24.0 OpenSSL/0.9.8r zlib/1.2.5 \r\n");
    client.print("Host: 145.48.6.30 \r\n");
    client.print("SOAPAction:localhost/Receive/storedata \r\n");
    client.print("Content-Type:text/xml;charset=utf-8 \r\n");
    client.print("Content-Length: "+ (String)content.length() + "\r\n");
    client.print("\r\n");
    client.print(content);
    //client.print("<soap:Envelope xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\"> <soap:Body>    <storedata xmlns=\"localhost/Receive/\">      <XbeeDataPoints><XbeeData>          <Time>1</Time> <Temperature>2</Temperature> <CO2>3</CO2> <Humidity>4</Humidity> <Light>5</Light> <NodeAdressLow>12345</NodeAdressLow> <NodeAdressHigh>67890</NodeAdressHigh> </XbeeData>      </XbeeDataPoints> </storedata> </soap:Body></soap:Envelope>");
    client.print("\r\n");
    //client.println();














    Serial.println("done building package");
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}







void loop()
{
  // if there are incoming bytes available 

  // from the server, read them and print them:
  //delay(1000);
  while(client.available()) {
    char c = client.read();
    Serial.print(c);


  }


  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");


    client.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }
}




