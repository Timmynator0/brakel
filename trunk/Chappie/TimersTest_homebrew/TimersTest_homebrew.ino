#include <Timers.h>
#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress server(173,194,34,18); // Google
EthernetClient client;

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
  Timers1.initialize(250,1); // delay in milliseconden,which timer
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

void fourthFunction(void)
{
  Serial1.write("koekjes");
}

void loop()
{
  // timer.update();

  // if there are incoming bytes available 
  // from the server, read them and print them:
  //  if (client.available()) 
  //  {
  //    char c = client.read();
  //    Serial.print(c);
  //  }
}

