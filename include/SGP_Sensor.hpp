#include "Adafruit_SGP40.h"
#include "Adafruit_SHT31.h"
#include "Arduino.h"

Adafruit_SGP40 sgp;
Adafruit_SHT31 sht31;

void sgpSetup(){

    if (! sgp.begin()){
    Serial.println("SGP40 sensor not found :(");
    while (1);
  }

  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1);
  }
  Serial.print("Found SHT3x + SGP40 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
}