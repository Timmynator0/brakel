#include <Event.h>
#include <Timer.h>
#include <Ethernet.h>
#include <SPI.h>

Timer timer;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress server(173,194,34,18); // Google
EthernetClient client;

String test = "koekjes";

void setup()
{
   //Open Serial communications and wait for port to open
  Serial.begin(9600);
  Serial.println("Starting Ethernet");
  if(Ethernet.begin(mac) == 0) 
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    //no point in carrying on, so do nothing.
    for(;;);
  }
  delay(1000);//give the Ethernetshield a second to initialize
  
  Serial.println("Connecting to the server...");
  //if you get a connection, report back via serial
  if(client.connect(server,80))
  {
   Serial.println("Connected"); 
   // Make a HTTP request:
   client.println("GET");
   client.println();
  }
  Serial1.begin(9600);
  initTimers(); 
}

void initTimers(void)
{
  int tickEvent = timer.every(100,firstFunction);
  Serial.print("0.1 second tick started with ID: ");
  Serial.println(tickEvent);
  tickEvent = timer.every(1000,secondFunction);
  Serial.print("1 second tick started with ID: ");
  Serial.println(tickEvent);
  tickEvent = timer.every(5100,thirdFunction);
  Serial.print("5.1 second tick started with ID: ");
  Serial.println(tickEvent);
}

void firstFunction(void)
{
  if (client.available()) 
  {
    char c = client.read();
    Serial.print(c);
  }
}

void secondFunction(void)
{
  Serial1.write("test");
}

void thirdFunction(void)
{
  Serial1.write(0x0C);
}

void loop()
{
  timer.update();
  
  // if there are incoming bytes available 
  // from the server, read them and print them:
//  if (client.available()) 
//  {
//    char c = client.read();
//    Serial.print(c);
//  }
}
