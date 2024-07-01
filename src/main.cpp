#include "includes.hpp"
uint32_t timerGPS = millis(); // this value integer will hold the current count value for our sketch
uint32_t timerSPG = millis();
uint32_t timerGFX = millis();
uint32_t timerIO = millis();
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

void loop()
{
  io.run();
  gpsLoop();
  screen::reset();
  if (millis() - timerSPG > 2500)
  {
    timerSPG = millis();
    sgpLoop();
  }
  if (millis() - timerGPS > 5000)
  {
    timerGPS = millis();
    // put your main code here, to run repeatedly:
    
    BMEloop();

    screen::canvas.print("H/T/V: ");
    screen::canvas.print(ReturnHumid()), screen::canvas.print(", ");
    screen::canvas.print(ReturnTemp()), screen::canvas.print(", "); 
    screen::canvas.println(returnVoc());

    gpsPrint();

    screen::draw();
    temper->save(ReturnTemp(), (double)GPS.latitude, (double)GPS.longitude, (double)GPS.altitude, (int)6);
    humidity->save(ReturnHumid(), (double)GPS.latitude, (double)GPS.longitude, (double)GPS.altitude, (int)6);
    pressure->save(ReturnPres(), (double)GPS.latitude, (double)GPS.longitude, (double)GPS.altitude, (int)6);
    quality->save(returnVoc(), (double)GPS.latitude, (double)GPS.longitude, (double)GPS.altitude, (int)6);
  }
}
