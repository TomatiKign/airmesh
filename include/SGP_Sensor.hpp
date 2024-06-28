#include "Adafruit_SGP40.h"
#include "Adafruit_SHT31.h"
#include "Arduino.h"
#include "BME_Sensor.hpp"
Adafruit_SGP40 sgp;

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)
void StartSGP(){

  if (! sgp.begin()){
    Serial.println("SGP40 sensor not found :(");
    while (1);
  }

  if (!bme.begin()) {
        Serial.println("Could not find a valid BME680 sensor, check wiring!");
        while (1);
    }

  Serial.print("Found BME688 + SGP40 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
}

void sgpLoop() {
  int32_t voc_index;
bme.setTemperatureOversampling(BME680_OS_8X);
    Temp = bme.temperature;
  bme.setHumidityOversampling(BME680_OS_2X);

    Humidity = bme.humidity;
 Serial.print("Temp *C = "); Serial.print(bme.temperature); Serial.print("\t\t");
   Serial.print("Hum. % = "); Serial.println(bme.humidity);
  voc_index = sgp.measureVocIndex(Temp, Humidity);
  Serial.print("Voc Index: ");
  Serial.println(voc_index);
  delay(1000);
}

