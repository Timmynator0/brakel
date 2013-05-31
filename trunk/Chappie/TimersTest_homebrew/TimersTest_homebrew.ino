#include <Timers.h>
#include <Ethernet.h>
#include <SPI.h>
#include <XBee1.h>

/**
 * INTERNET STUFF
 */
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress server(173,194,34,17); // Google
EthernetClient client;

float temperature = -1;
float humidity = -1;
float lightIntensity = -1;

/**
 * XBEE STUFF 
 */
XBee xbee = XBee();
XBeeResponse resp;

void setup()
{
  initTimers(); 
  //Open Serial communications and wait for port to open
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Starting Ethernet");
  if(Ethernet.begin(mac) == 0) 
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    //no point in carrying on, so do nothing.
    for(;;);
  }
 // delay(1000);//give the Ethernetshield a second to initialize

  Serial.println("Connecting to the server...");
  //if you get a connection, report back via serial
  if(client.connect(server,80))
  {
    Serial.println("Connected"); 
    // Make a HTTP request:
    client.println("GET");
    client.println();
  }
  
 xbee.setSerial(Serial);
  
}

void initTimers(void)
{
  Timers1.initialize(5000,1); // delay in milliseconden,which timer
  Timers1.attachInterruptTimer1(firstFunction);

  Timers3.initialize(1000,3);
  Timers3.attachInterruptTimer3(secondFunction);

  Timers4.initialize(6000,4);
  Timers4.attachInterruptTimer4(thirdFunction);

  Timers5.initialize(2000,5);
  Timers5.attachInterruptTimer5(fourthFunction);

}

void firstFunction(void)
{
  //  if (client.available()) 
  //  {
  //    char c = client.read();
  //    Serial.print(c);
  //  }
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Light Intensity: ");
  Serial.println(lightIntensity);
}

void secondFunction(void)
{
  Serial1.write("test");
}

void thirdFunction(void)
{
  Serial1.write(0x0C);
}

void fourthFunction(void)
{
  Serial1.write("koekjes");
}

void loop()
{
  xbee.readPacket();
  if ( xbee.getResponse().isAvailable() )
  { 
    // get response
    resp = xbee.getResponse();
    if(xbee.getResponse().getApiId() == ZB_IO_SAMPLE_RESPONSE)
    {
      ZBRxIoSampleResponse response = ZBRxIoSampleResponse();
      resp.getZBRxIoSampleResponse(response);
      if(response.containsAnalog())
      {
        //parse and save locally
        temperature = (response.getAnalog(1)/1023.f*1.22f-0.5f)*100;
        humidity = response.getAnalog(2)/10.f;
        lightIntensity = response.getAnalog(3)/10.23f;
      }
    }
  }
  else
    Serial.println("No node Available!"); 
    delay(3000);
}





