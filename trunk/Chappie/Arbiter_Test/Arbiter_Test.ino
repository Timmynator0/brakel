#include <SD.h>
#include <Timers.h>
#include <Ethernet.h>
#include <SPI.h>

File myReadFile;
File myWriteFile;

// bool to indicate wheter or not the file is beining used by an other timer
volatile bool writing_lock = false;
volatile bool reading_lock = false;
volatile int readingTimes = 0;
volatile int writingTimes = 0;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial1.begin(9600);
  initSD();
  delay(100);
  initTimers();

}

void loop()
{

}

void initSD()
{
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(53, OUTPUT);

  if (!SD.begin(4)) {
    Serial.println("initialization SD card failed!");
    return;
  }
  writeSD();
  Serial.println("initialization SD card done.");
}

void initTimers()
{
  Serial.print("12init timers");
  delay(50);
  Timers1.initialize(500,1); // delay in milliseconden,which timer
  delay(50);
  Timers1.attachInterruptTimer1(readAction);
  delay(50);

  Timers3.initialize(1000,3);
  delay(50);
  Timers3.attachInterruptTimer3(readAction2);
  delay(50);

  Timers4.initialize(2000,4);
  delay(50);
  Timers4.attachInterruptTimer4(writeAction);
  delay(50);

  Timers5.initialize(500,5);
  delay(50);
  Timers5.attachInterruptTimer5(WriteToDisplay);
  delay(50);

  Serial.println("init timers DONE!");
}

void WriteToDisplay()
{
  Serial1.write(0x0C);
  Serial1.print("Writing Times: ");
  Serial1.print(writingTimes);
  Serial1.write("\r\n");
  Serial1.print("Reading Times: ");
  Serial1.print(readingTimes);
}

void writeAction()
{
  while(writing_lock)
  { 
    ;
  }
  writing_lock = true;
  Serial.println("writing");
  writeSD();
  writing_lock = false;
}

void readAction()
{        
  while(reading_lock)
  {
    ;
  }
  reading_lock = true;
  Serial.println("reading from the first timer");
  readSD();
  reading_lock = false;
}

void readAction2()
{
  while(reading_lock)
  {
    ;
  }
  reading_lock = true;
  Serial.println("Reading from the second timer");
  readSD();
  reading_lock = false;
}

void readSD()
{
  // re-open the file for reading:
  while(writing_lock)
  { 
    ;
  }
  writing_lock = true;
  myReadFile = SD.open("test.txt");
  writing_lock = false;
  if (myReadFile) {
    //Serial.println("test.txt:");
    readingTimes++;
    Serial.print("readed: ");
    Serial.println(readingTimes);
    // read from the file until there's nothing else in it:
    /*while (myReadFile.available())
     		{
     			Serial.println(myReadFile.readString());
     
     		}*/
    //Serial.write("DONE READING!");
    // close the file:
    myReadFile.close();
  } 
  else 
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt Read 1");
  }
}

int i = 0;
void writeSD()
{
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myWriteFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myWriteFile) {
    //erial.print("Writing to test.txt...");
    //	String data = "Number  test test test !";
    myWriteFile.print("Number : ");
    myWriteFile.println(i);
    //Serial.println(i);
    i ++ ;

    // close the file:
    myWriteFile.close();
    writingTimes++;
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}





