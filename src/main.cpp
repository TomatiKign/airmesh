/**
 * @file main.cpp
 * @brief main function executing the program
 */

#include "includes.hpp"

/**
 * @brief variables to hold timer information for sensors and adafruit io. used to control how frequently the programs are ran
 */

uint32_t timerGPS = millis(); // this value integer will hold the current count value for our sketch
uint32_t timerSGP = millis();
uint32_t timerGFX = millis();
uint32_t timerIO = millis();

/**
 * @brief setup for the serial monitor and all sensors; updates will be printed onto the screen
 */

void setup()
{
  screen::init();

  screen::set_status("Initializing Serial Monitor...");
  Serial.begin(115200);
  while (!Serial)
  {
    delay(10);
  }

  screen::set_status("Initializing GPS...");
  gpsStart();

  screen::set_status("Initializing SGP & BME...");
  if (!sgp.begin())
  {
    screen::set_status("SGP40 sensor not found :(");
    while (1)
      ;
  }

  if (!bme.begin())
  {
    screen::set_status("Could not find a valid BME680 sensor, check wiring!");
    while (1)
      ;
  }
  ioSetup();
  screen::set_status("Finished setup");
}

/**
 * @brief loop function that runs the screen, serial monitor, and adafruit io connections
 */

void loop()
{
  io.run();
  gpsLoop();
  screen::reset();

  /**
   * @brief creates timers for how often each sensor will be ran independently of the other sensors
   */

  if (millis() - timerSGP > 2500)
  {
    timerSGP = millis();
    sgpLoop();
  }
  if (millis() - timerGPS > 5000)
  {
    timerGPS = millis();
    // put your main code here, to run repeatedly:
    
    BMEloop();

    /**
     * @brief prints humidity, temperature, and VOC index to the serial monitor
     */

    screen::canvas.print("H/T/V: ");
    screen::canvas.print(GetHumid()), screen::canvas.print(", ");
    screen::canvas.print(GetTemp()), screen::canvas.print(", "); 
    screen::canvas.println(GetVoc());

    gpsPrint();

    /**
     * @brief if the GPS sensor is connected to a satellite begin to save data values to adafruit io with location
     */

    screen::draw();
    if(GPS.fixquality == 1){
      temper->save(GetTemp(), (double)GPS.latitude, (double)GPS.longitude, (double)GPS.altitude, 6);
      humidity->save(GetHumid(), (double)GPS.latitude, (double)GPS.longitude, (double)GPS.altitude, 6);
      pressure->save(GetPressure(), (double)GPS.latitude, (double)GPS.longitude, (double)GPS.altitude, 6);
      quality->save(GetVoc(), (double)GPS.latitude, (double)GPS.longitude, (double)GPS.altitude, 6);
    }
  }
}