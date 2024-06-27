#include <Arduino.h>
#include <Adafruit_GPS.h>    // GPS Sensor
#include <Adafruit_GFX.h>    // Core graphics library
#include <sensors/gfxThings.hpp>

Adafruit_GPS GPS(&Wire);
#define GPSECHO false

// every IO_LOOP_DELAY milliseconds
#define IO_LOOP_DELAY 5000
//asdasdas

uint8_t hours = GPS.hour;          ///< GMT hours
uint8_t mins = GPS.minute;        ///< GMT minutes
uint8_t secs = GPS.seconds;      ///< GMT seconds

double rlat = 0; //received latitude
double rlon = 0; //received longitude
double rele = 0; //reveived elevation

void gpsSetup(){
  GPS.begin(0x10); 
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); 
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
  GPS.println(PMTK_Q_RELEASE);
}

void gpsLoop(){
    char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if (GPSECHO)
    if (c) Serial.print(c);
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data 
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trying to print out data
    Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to parse a sentence in which case we should just wait for another
  }


    Serial.print("\nTime: ");
    if (GPS.hour < 10) { Serial.print('0'); }
    Serial.print(GPS.hour, DEC); Serial.print(':');
    if (GPS.minute < 10) { Serial.print('0'); }
    Serial.print(GPS.minute, DEC); Serial.print(':');
    if (GPS.seconds < 10) { Serial.print('0'); }
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    if (GPS.milliseconds < 10) {
      Serial.print("00");
    } else if (GPS.milliseconds > 9 && GPS.milliseconds < 100) {
      Serial.print("0");
    }
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
   if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    }


    //TFT PRINTING
    clear();
    tft.print("Time"); 
    if (GPS.hour < 10) { tft.print('0'); }
    tft.print(GPS.hour, DEC); tft.print(':');
    if (GPS.minute < 10) { tft.print('0'); }
    tft.print(GPS.minute, DEC); tft.print(':');
    if (GPS.seconds < 10) { tft.print('0'); }
    tft.println(GPS.seconds, DEC); 
    
    tft.print("Time"); tft.setTextSize(1); tft.print("(last seen)"); tft.setTextSize(2); tft.print(": ");
    if (GPS.fixquality == 1)
    {
      hours = GPS.hour;
      mins = GPS.minute;
      secs = GPS.seconds;
      
    }
    if (hours < 10) { tft.print('0'); }
    tft.print(hours, DEC); tft.print(':');
    if (mins < 10) { tft.print('0'); }
    tft.print(mins, DEC); tft.print(':');
    if (secs < 10) { tft.print('0'); }
    tft.println(secs, DEC); 

    tft.print("Date: ");
    tft.print(GPS.day, DEC); tft.print('/');
    tft.print(GPS.month, DEC); tft.print("/20");
    tft.println(GPS.year, DEC);
    tft.print("Fix: "); tft.print((int)GPS.fix);
    tft.print(" quality: "); tft.println((int)GPS.fixquality);
    
    tft.print("Long: "); 
    tft.println(GPS.longitude);
    tft.print("Lat: ");
    tft.println(GPS.latitude);
    tft.print("Altitude: "); 
    tft.println(GPS.altitude);
    }