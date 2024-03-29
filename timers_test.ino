#include <SD.h>
#include <Event.h>
#include <Timer.h>

File myReadFile;
File myWriteFile;

// bool to indicate wheter or not the file is beining used by an other timer
volatile bool busy_lock = false;
volatile bool reading_lock = false;

//the timers to read/write
Timer writer;
Timer reader;

void setup()
{
        // Open serial communications and wait for port to open:
	Serial.begin(9600);
        initSD();
        writeSD();
        initTimers();
}

void loop()
{
       writer.update();
       reader.update();
}


void initTimers()
{
	// Initialize the SD card
	initSD();
	// Initialize the write timer to fire an event every 2 seconds
	int tickEvent = writer.every(14000, writeAction);
	Serial.print("14 second tick started id=");
	Serial.println(tickEvent);	
	tickEvent = reader.every(4000, readAction);
        Serial.print("4 second tick started id=");
	Serial.println(tickEvent);
        tickEvent = reader.every(10000, readAction2);
        Serial.print("10 sec tick started id=");
        Serial.println(tickEvent);
}

void writeAction()
{
          while(busy_lock)
          { ;}
          busy_lock = true;
	  Serial.println("writing");
	  writeSD();
          busy_lock = false;
        
}

void readAction()
{        
        while(reading_lock)
        {;}
        reading_lock = true;
	Serial.println("reading from timer1");
	readSD();
        reading_lock = false;
}

void readAction2()
{
       while(reading_lock)
       {;}
       reading_lock = true;
       Serial.println("Reading from timer2");
       readSD();
       reading_lock = false;
}

void initSD()
{
	Serial.print("Initializing SD card...");
	// On the Ethernet Shield, CS is pin 4. It's set as an output by default.
	// Note that even if it's not used as the CS pin, the hardware SS pin 
	// (10 on most Arduino boards, 53 on the Mega) must be left as an output 
	// or the SD library functions will not work. 
	pinMode(10, OUTPUT);

	if (!SD.begin(4)) {
		Serial.println("initialization SD card failed!");
		return;
	}
	Serial.println("initialization SD card done.");
}

void readSD()
{
	// re-open the file for reading:
        while(busy_lock)
        { ;}
        busy_lock = true;
	myReadFile = SD.open("test.txt");
        busy_lock = false;
	if (myReadFile) {
		//Serial.println("test.txt:");

		// read from the file until there's nothing else in it:
		while (myReadFile.available())
		{
			Serial.println(myReadFile.readString());

		}
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

	} else {
		// if the file didn't open, print an error:
		Serial.println("error opening test.txt");
	}
}