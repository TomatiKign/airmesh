#include <Arduino.h>
#include <Adafruit_GPS.h>    // GPS Sensor

Adafruit_GPS GPS(&Wire);
#define GPSECHO false

// every IO_LOOP_DELAY milliseconds
#define IO_LOOP_DELAY 5000



void gpsStart(){
  GPS.begin(0x10); 
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); 
  GPS.sendCommand(PGCMD_ANTENNA);
  GPS.println(PMTK_Q_RELEASE);
  
}

//location->save(value, GPS.latitude, GPS.longitude, GPS.altitude);

/*
*/