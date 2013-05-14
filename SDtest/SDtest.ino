#include <SD.h>
#include <Time.h>
#include <string.h>
File myFile;
int i ;
int daycount;
int nodeCount;
int nodeValue;
void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) 
   {
    ; // wait for serial port to connect. Needed for Leonardo only
   }
   
   nodeCount = 0;
     Serial.println("initialization done., waiting 5 seconds for SD :3");

  delay(5000);
  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
   pinMode(10, OUTPUT);
   
  if (!SD.begin(4)) 
  {
    Serial.println("initialization failed!");
    return;
  }
   Serial.println("initialization done.");
}

void loop()
{
	Serial.println("woke up!");
	time_t t = now();
	Serial.print("the time is: ");
	Serial.println(t);

	if(t >= 86400) //if a day has passed, reset the day! 
	{
		Serial.println("a day has passed!");
		setTime(0); // day has passed, reset the day!
		daycount++;
		i = 0;
	} 
	
	//Serial.println(t);
	WriteSD();

	//Serial.println("started reading");
	//ReadSD();
	Serial.println("sleeping!");
	delay(300000); //wait 5 minutes, start  300000ms
}

void WriteSD()
{
	
  String Filename = "logs/";
	String days = String(daycount);
	String extension = ".txt";
	String string = "" ;
	
	
	days.concat(".txt");
	Filename.concat(days);
	Serial.print("file is: ");
	Serial.println(Filename);
	//char * buff;j
	 //char * filename = days.toCharArray(buff,10,0);
	 char __dataFileName[sizeof(Filename)];
    Filename.toCharArray(__dataFileName, sizeof(__dataFileName));

//days += extension ;
  myFile = SD.open( __dataFileName , FILE_WRITE);
  Serial.println(__dataFileName);
  // if the file opened okay, write to it:
  if (myFile) 
  {

	//myFile.print(days);

	while(nodeCount != 51)
	{
		nodeValue = random(0,50);
		myFile.print("node : ");
		myFile.print(nodeCount);
		myFile.print(" value= ");
		myFile.println(nodeValue);
		nodeCount ++;
	}
	nodeCount = 0;
	//myFile.println(" +  write i");
	Serial.println("i wrote 50 lines");

   
    // close the file:
    myFile.close();
    
  } 
  else
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  
}

void ReadSD()
{
	  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
        //

    }
	Serial.write("DONE READING!");
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
