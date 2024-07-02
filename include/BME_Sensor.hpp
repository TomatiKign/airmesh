#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME680 bme;

/**
 * @brief creates floats to store data which the BME sensor collects
 */

float Temp = 0;
float Pressure = 0;
float Humidity = 0;
float GasRes = 0;
float Altitude = 0;

/**
 * @brief initializes the BME688 Sensor
 * @note must be ran before the sensor can be used
 */

void StartBME() {
    if (!bme.begin()) {
        Serial.println("Could not find a valid BME680 sensor, check wiring!");
        while (1);
    }
}

/**
 * @brief calls temperature from BME sensor and returns it
 * @return float of temperature in Celsius
 */

float GetTemp() {
    bme.setTemperatureOversampling(BME680_OS_8X);
    Temp = bme.temperature;
    
    return Temp;
}

/**
 * @brief calls pressure from BME sensor and returns it
 * @return float of pressure in centiPascals
 */

float GetPressure() {
    bme.setPressureOversampling(BME680_OS_4X);

    Pressure = bme.pressure / 100;

    return Pressure;
}

/**
 * @brief calls humidity from BME sensor and returns it
 * @return float of relative humidity percentage
 */

float GetHumid() {
    bme.setHumidityOversampling(BME680_OS_2X);

    Humidity = bme.humidity;
    
    return Humidity;
}

/**
 * @brief calls gas resistance from BME sensor and returns it
 * @return float of gas resistance in kiloOhms
 */

float GetGasResist() {
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms
    
    GasRes = bme.gas_resistance / 1000;

    return GasRes;
}

/**
 * @brief calls altitude from BME sensor and returns it
 * @return float of altitude in hPa
 */

float GetAlt() {
    Altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
    
    return Altitude;
}

/**
 * @brief loop that prints the BME sensor information to the serial monitor
 * @warning this will not print the altitude to the serial monitor
 */

void BMEloop() {
  Serial.print("Temperature = ");
  Serial.print(GetTemp());
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(GetPressure());
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(GetHumid());
  Serial.println(" %");

  Serial.print("Gas = ");
  Serial.print(GetGasResist());
  Serial.println(" KOhms");

  Altitude = GetAlt();
}