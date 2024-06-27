#include "includes.hpp"

void setup() {
  screen::init();
  
  screen::set_status("Initializing Serial Monitor");
  Serial.begin(115200);
  while (!Serial) { delay(10); } // Wait for serial console to open!
  
  screen::set_status("Finished setup");
}


void loop() {
  // put your main code here, to run repeatedly:
}
