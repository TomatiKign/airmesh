//libraries
#include <Arduino.h>
#include <Adafruit_GPS.h>    // GPS Sensor
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include "Adafruit_SGP40.h" //SGP Sensor library config
#include "Adafruit_SHT31.h" //SGP Sensor
#include "Adafruit_MQTT.h"
#include "ArduinoHttpClient.h"
#include <Adafruit_Sensor.h>   // FOR BME
#include <Wire.h> //FOR BME
#include <SPI.h>  // FOR BME
#include "Adafruit_BME680.h" //BME Sensor

//other files
#include <config.hpp> // adafruit wifi config
#include <GPS_Sensor.hpp> // runs gps sensor
#include <SGP_Sensor.hpp> // runs sgp sensor
#include <screen.hpp> // esp32-s3 tft screen config
#include <IO_config.hpp> // adafruit io config