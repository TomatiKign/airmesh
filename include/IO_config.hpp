#include <Arduino.h>
#include <SPI.h>
#include <config.hpp>

AdafruitIO_Feed *temper = io.feed("airmesh.temp");
AdafruitIO_Feed *quality = io.feed("airmesh.quality");
AdafruitIO_Feed *humidity = io.feed("airmesh.humidity");
AdafruitIO_Feed *pressure = io.feed("airmesh.pressure");

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