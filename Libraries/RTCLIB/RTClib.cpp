// Code by JeeLabs http://news.jeelabs.org/code/
// Released to the public domain! Enjoy!

#include <Wire.h>
#include "Arduino.h"
#include <avr/pgmspace.h>
#include "RTClib.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>



#define DS1307_ADDRESS 0x68
#define SECONDS_PER_DAY 86400L

#define SECONDS_FROM_1970_TO_2000 946684800

#if (ARDUINO >= 100)
 #include <Arduino.h> // capital A so it is error prone on case-sensitive filesystems
#else
 #include <WProgram.h>
#endif

RTC_DS1307 RTC2;

byte timeServer2[]={193, 79, 237, 14};
byte mac2[] = { 0x90, 0xA2, 0xDA, 0x00, 0x8D, 0x40 };

EthernetUDP Udp2;
const int NTP_PACKET_SIZE2= 48;
byte pb2[NTP_PACKET_SIZE2];
unsigned int localPort2 = 8888;

//File myFile;

int count;
int daycount;
int nodeCount;
int nodeValue;



int i = 0; //The new wire library needs to take an int when you are sending for the zero register
////////////////////////////////////////////////////////////////////////////////
// utility code, some of this could be exposed in the DateTime API if needed

const uint8_t daysInMonth [] PROGMEM = { 31,28,31,30,31,30,31,31,30,31,30,31 }; //has to be const or compiler compaints

// number of days since 2000/01/01, valid for 2001..2099
static uint16_t date2days(uint16_t y, uint8_t m, uint8_t d) {
    if (y >= 2000)
        y -= 2000;
    uint16_t days = d;
    for (uint8_t i = 1; i < m; ++i)
        days += pgm_read_byte(daysInMonth + i - 1);
    if (m > 2 && y % 4 == 0)
        ++days;
    return days + 365 * y + (y + 3) / 4 - 1;
}

static long time2long(uint16_t days, uint8_t h, uint8_t m, uint8_t s) {
    return ((days * 24L + h) * 60 + m) * 60 + s;
}

////////////////////////////////////////////////////////////////////////////////
// DateTime implementation - ignores time zones and DST changes
// NOTE: also ignores leap seconds, see http://en.wikipedia.org/wiki/Leap_second

DateTime::DateTime (uint32_t t) {
  t -= SECONDS_FROM_1970_TO_2000;    // bring to 2000 timestamp from 1970

    ss = t % 60;
    t /= 60;
    mm = t % 60;
    t /= 60;
    hh = t % 24;
    uint16_t days = t / 24;
    uint8_t leap;
    for (yOff = 0; ; ++yOff) {
        leap = yOff % 4 == 0;
        if (days < 365 + leap)
            break;
        days -= 365 + leap;
    }
    for (m = 1; ; ++m) {
        uint8_t daysPerMonth = pgm_read_byte(daysInMonth + m - 1);
        if (leap && m == 2)
            ++daysPerMonth;
        if (days < daysPerMonth)
            break;
        days -= daysPerMonth;
    }
    d = days + 1;
}

DateTime::DateTime (uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) {
    if (year >= 2000)
        year -= 2000;
    yOff = year;
    m = month;
    d = day;
    hh = hour;
    mm = min;
    ss = sec;
}

static uint8_t conv2d(const char* p) {
    uint8_t v = 0;
    if ('0' <= *p && *p <= '9')
        v = *p - '0';
    return 10 * v + *++p - '0';
}

// A convenient constructor for using "the compiler's time":
//   DateTime now (__DATE__, __TIME__);
// NOTE: using PSTR would further reduce the RAM footprint
DateTime::DateTime (const char* date, const char* time) {
    // sample input: date = "Dec 26 2009", time = "12:34:56"
    yOff = conv2d(date + 9);
    // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec 
    switch (date[0]) {
        case 'J': m = date[1] == 'a' ? 1 : m = date[2] == 'n' ? 6 : 7; break;
        case 'F': m = 2; break;
        case 'A': m = date[2] == 'r' ? 4 : 8; break;
        case 'M': m = date[2] == 'r' ? 3 : 5; break;
        case 'S': m = 9; break;
        case 'O': m = 10; break;
        case 'N': m = 11; break;
        case 'D': m = 12; break;
    }
    d = conv2d(date + 4);
    hh = conv2d(time);
    mm = conv2d(time + 3);
    ss = conv2d(time + 6);
}

uint8_t DateTime::dayOfWeek() const {    
    uint16_t day = date2days(yOff, m, d);
    return (day + 6) % 7; // Jan 1, 2000 is a Saturday, i.e. returns 6
}

uint32_t DateTime::unixtime(void) const {
  uint32_t t;
  uint16_t days = date2days(yOff, m, d);
  t = time2long(days, hh, mm, ss);
  t += SECONDS_FROM_1970_TO_2000;  // seconds from 1970 to 2000

  return t;
}

////////////////////////////////////////////////////////////////////////////////
// RTC_DS1307 implementation

static uint8_t bcd2bin (uint8_t val) { return val - 6 * (val >> 4); }
static uint8_t bin2bcd (uint8_t val) { return val + 6 * (val / 10); }

uint8_t RTC_DS1307::begin(void) {
  return 1;
}


#if (ARDUINO >= 100)

uint8_t RTC_DS1307::isrunning(void) {
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(i);	
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 1);
  uint8_t ss = Wire.read();
  return !(ss>>7);
}

void RTC_DS1307::adjust(const DateTime& dt) {
    Wire.beginTransmission(DS1307_ADDRESS);
    Wire.write(i);
    Wire.write(bin2bcd(dt.second()));
    Wire.write(bin2bcd(dt.minute()));
    Wire.write(bin2bcd(dt.hour()));
    Wire.write(bin2bcd(0));
    Wire.write(bin2bcd(dt.day()));
    Wire.write(bin2bcd(dt.month()));
    Wire.write(bin2bcd(dt.year() - 2000));
    Wire.write(i);
    Wire.endTransmission();
}

DateTime RTC_DS1307::now() {
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(i);	
  Wire.endTransmission();
  
  Wire.requestFrom(DS1307_ADDRESS, 7);
  uint8_t ss = bcd2bin(Wire.read() & 0x7F);
  uint8_t mm = bcd2bin(Wire.read());
  uint8_t hh = bcd2bin(Wire.read());
  Wire.read();
  uint8_t d = bcd2bin(Wire.read());
  uint8_t m = bcd2bin(Wire.read());
  uint16_t y = bcd2bin(Wire.read()) + 2000;
  
  return DateTime (y, m, d, hh, mm, ss);
}





#else

uint8_t RTC_DS1307::isrunning(void) {
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.send(i);	
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 1);
  uint8_t ss = Wire.receive();
  return !(ss>>7);
}

void RTC_DS1307::adjust(const DateTime& dt) {
    Wire.beginTransmission(DS1307_ADDRESS);
    Wire.send(i);
    Wire.send(bin2bcd(dt.second()));
    Wire.send(bin2bcd(dt.minute()));
    Wire.send(bin2bcd(dt.hour()));
    Wire.send(bin2bcd(0));
    Wire.send(bin2bcd(dt.day()));
    Wire.send(bin2bcd(dt.month()));
    Wire.send(bin2bcd(dt.year() - 2000));
    Wire.send(i);
    Wire.endTransmission();
}

DateTime RTC_DS1307::now() {
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.send(i);	
  Wire.endTransmission();
  
  Wire.requestFrom(DS1307_ADDRESS, 7);
  uint8_t ss = bcd2bin(Wire.receive() & 0x7F);
  uint8_t mm = bcd2bin(Wire.receive());
  uint8_t hh = bcd2bin(Wire.receive());
  Wire.receive();
  uint8_t d = bcd2bin(Wire.receive());
  uint8_t m = bcd2bin(Wire.receive());
  uint16_t y = bcd2bin(Wire.receive()) + 2000;
  
  return DateTime (y, m, d, hh, mm, ss);
}



#endif


////////////////////////////////////////////////////////////////////////////////
// RTC_Millis implementation

long RTC_Millis::offset = 0;

void RTC_Millis::adjust(const DateTime& dt) {
    offset = dt.unixtime() - millis() / 1000;
}

DateTime RTC_Millis::now() {
  return (uint32_t)(offset + millis() / 1000);
}

////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////
                ///NTP///
/////////////////////////////////////////
void NTP::init(){
  
    if(getYear()== 2000 || getYear() < 2013)
        sendRequest();
    
    if(getHour() == 14 && getMinute() == 56 && getSecond() == 0)
        sendRequest();
  
}


void NTP::setup(){
    
    int DHCP2 = 0;
    DHCP2 = Ethernet.begin(mac2);
    if(DHCP2)
        Serial.println("DHCP Success");
    else
        Serial.println("DHCP Failed");

    Udp2.begin(localPort2);
    Wire.begin();
    RTC2.begin();
    
    nodeCount = 0;

}

void NTP::sendRequest(){
    
   
    sendNTPpacket2(timeServer2);
    delay(100);
    if(Udp2.parsePacket()){
        Serial.println("UDP available2");
        Udp2.read(pb2, NTP_PACKET_SIZE2);
        unsigned long t1, t2, t3, t4;
        t1 = t2 = t3 = t4 = 0;
        for (int i=0; i< 4; i++)
        {
            t1 = t1 << 8 | pb2[16+i];
            t2 = t2 << 8 | pb2[24+i];
            t3 = t3 << 8 | pb2[32+i];
            t4 = t4 << 8 | pb2[40+i];
        }
        
        // part of the fractional part
        // could be 4 bytes but this is more precise than the 1307 RTC
        // which has a precision of ONE second
        // in fact one byte is sufficient for 1307
        float f1,f2,f3,f4;
        f1 = ((long)pb2[20] * 256 + pb2[21]) / 65536.0;
        f2 = ((long)pb2[28] * 256 + pb2[29]) / 65536.0;
        f3 = ((long)pb2[36] * 256 + pb2[37]) / 65536.0;
        f4 = ((long)pb2[44] * 256 + pb2[45]) / 65536.0;
        
               
        // convert NTP to UNIX time, differs seventy years = 2208988800 seconds
        // NTP starts Jan 1, 1900
        // Unix time starts on Jan 1 1970.
        const unsigned long seventyYears2 = 2208988800UL;
        t1 -= seventyYears2;
        t2 -= seventyYears2;
        t3 -= seventyYears2;
        t4 -= seventyYears2;

        
        PrintDateTime(DateTime(t4));
        Serial.println(f4,4);
        Serial.println();
        
        // Time zone instellen
        t4 += (2 * 3600L);     
        t4 += 1;               // adjust the delay(1000) at 
        RTC2.adjust(DateTime(t4));
        
        Serial.print("RTC after : ");
        PrintDateTime(RTC2.now());
        Serial.println();
        
        Serial.println("Updated...");

        
    }else{
        Serial.println("UDP not available2");
    }
    
}


unsigned long NTP::sendNTPpacket2(byte *address){
    memset(pb2, 0, NTP_PACKET_SIZE2);
    pb2[0] = 0b11100011;
    pb2[1] = 0;
    pb2[2] = 6;
    pb2[3] = 0xEC;
    pb2[12]  = 49;
    pb2[13]  = 0x4E;
    pb2[14]  = 49;
    pb2[15]  = 52;
    Udp2.beginPacket(address, 123);
    Udp2.write(pb2,NTP_PACKET_SIZE2);
    Udp2.endPacket();
    
}
    
void NTP::PrintDateTime(DateTime t)
{
    char datestr[24];
    sprintf(datestr, "%04d-%02d-%02d  %02d:%02d:%02d  ", t.year(), t.month(), t.day(), t.hour(), t.minute(), t.second());
    Serial.println(datestr);
}

void NTP::PrintDateTime()
{
    DateTime t = RTC2.now();
    char datestr[24];
    sprintf(datestr, "%02d-%02d-%04d  %02d:%02d:%02d  ", t.day(), t.month(), t.year(), t.hour(), t.minute(), t.second());
    Serial.println(datestr);
}

int NTP::getYear(){
    time = RTC2.now();
    return time.year();
}


int NTP::getHour(){
    time = RTC2.now();
    return time.hour();
    
}

int NTP::getMinute(){
    time = RTC2.now();
    return time.minute();
    
}

int NTP::getSecond(){
    time = RTC2.now();
    return time.second();
}

char* NTP::getDateSD(){
    DateTime t = RTC2.now();
    char *result = "T";
    sprintf(result,"%02d%02d%02d.txt",t.day(),t.month(),t.year());
    return result;
}

DateTime NTP::GetDateTime()
{
   return DateTime t = RTC2.now();
    
}

    



