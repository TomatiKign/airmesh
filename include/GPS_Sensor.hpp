#include <Arduino.h>
#include <Adafruit_GPS.h>    // GPS Sensor

Adafruit_GPS GPS(&Wire);
#define GPSECHO false

// every IO_LOOP_DELAY milliseconds
#define IO_LOOP_DELAY 5000
//asdasdas

int hours = GPS.hour;
int mins = GPS.minute;
int secs = GPS.seconds;
int day = GPS.day;
int month = GPS.month;
int year = GPS.year;

double lat = 0; //received latitude
double lon = 0; //received longitude
double alt = 0; //reveived altitude

void gpsStart(){
  delay(1000);
  GPS.begin(0x10); 
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); 
  GPS.sendCommand(PGCMD_ANTENNA);
  GPS.println(PMTK_Q_RELEASE);
}

/**
 * @brief Return time in hour
 * 
 * @return int 
 */

int returnHour() {
  char h = GPS.read();

  if (GPSECHO){
    if (h) Serial.print(h);
  }
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())){
      return;
    }
  }

  hours = GPS.hour;

  return hours;
}

/**
 * @brief Return time in minutes
 * 
 * @return int 
 */

int returnMin() {
  char m = GPS.read();

  if (GPSECHO){
    if (m) Serial.print(m);
  }
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())){
      return;
    }
  }

  mins = GPS.minute;

  return mins;
}

/**
 * @brief Return time in second
 * 
 * @return int 
 */

int returnSec() {
  char s = GPS.read();

  if (GPSECHO){
    if (s) Serial.print(s);
  }
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())){
      return;
    }
  }

  secs = GPS.seconds;

  return secs;
}

/**
 * @brief Return date in day
 * 
 * @return int 
 */

int returnDay() {
  char d = GPS.read();

  if (GPSECHO){
    if (d) Serial.print(d);
  }
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())){
      return;
    }
  }

  day = GPS.day;

  return day;
}

/**
 * @brief Return date in month
 * 
 * @return int 
 */

int returnMonth() {
  char mo = GPS.read();

  if (GPSECHO){
    if (mo) Serial.print(mo);
  }
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())){
      return;
    }
  }

  month = GPS.month;

  return month;
}

/**
 * @brief Return date in year
 * 
 * @return int 
 */

int returnYear() {
  char y = GPS.read();

  if (GPSECHO){
    if (y) Serial.print(y);
  }
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())){
      return;
    }
  }

  year = GPS.year;

  return year;
}

/**
 * @brief Return longitude
 * 
 * @return int 
 */

int returnLongitude() {
  char lo = GPS.read();

  if (GPSECHO){
    if (lo) Serial.print(lo);
  }
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())){
      return;
    }
  }

  lon = GPS.longitude;

  return lon;
}

/**
 * @brief Return latitude
 * 
 * @return int 
 */

int returnLatitude() {
  char la = GPS.read();

  if (GPSECHO){
    if (la) Serial.print(la);
  }
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())){
      return;
    }
  }

  lat = GPS.latitude;

  return lat;
}

/**
 * @brief Return altitude
 * 
 * @return int 
 */

int returnAltitude() {
  char al = GPS.read();

  if (GPSECHO){
    if (al) Serial.print(al);
  }
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA())){
      return;
    }
  }

  alt = GPS.altitude;

  return alt;
}