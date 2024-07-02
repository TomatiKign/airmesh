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

/**
 * @brief loop that cheks the temperature and humidity and uses them to calculate a VOC index which is printed to the serial monitor
 */

void sgpLoop() {
  int32_t voc_index;
  bme.setTemperatureOversampling(BME680_OS_8X);
  Temp = bme.temperature;
  bme.setHumidityOversampling(BME680_OS_2X);
  Humidity = bme.humidity;
  voc_index = sgp.measureVocIndex(Temp, Humidity);
  Serial.print("Voc Index: ");
  Serial.println(voc_index);
}

/**
 * @brief takes temperature and humidity from the BME sensor to calculate the VOC index
 * @return float of the VOC index
 */

float GetVoc(){
  bme.setTemperatureOversampling(BME680_OS_8X);
  Temp = bme.temperature;
  bme.setHumidityOversampling(BME680_OS_2X);
  Humidity = bme.humidity;
  return sgp.measureVocIndex(Temp, Humidity);
}
