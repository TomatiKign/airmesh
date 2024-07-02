#include <Arduino.h>
#include <SPI.h>
#include <config.hpp>

/**
 * @brief sets up the adafruit io feeds which data will be sent to
 * @note *{name} are the names of the feed in code, "{name}" refers to the feed names on adafruit io
 */

AdafruitIO_Feed *temper = io.feed("airmesh.temp");
AdafruitIO_Feed *quality = io.feed("airmesh.quality");
AdafruitIO_Feed *humidity = io.feed("airmesh.humidity");
AdafruitIO_Feed *pressure = io.feed("airmesh.pressure");

/**
 * @brief establishes a connection to adafruit io
 */

void ioSetup(){
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}