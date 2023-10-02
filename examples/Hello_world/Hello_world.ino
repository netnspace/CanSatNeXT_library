/*
  This example shows the most basic things - print a message and blink the on-board LED.

  If this doesn't work, it is most likely caused by one of these things
  1. The computer doesn't detect the device - check that the driver is installed
  2. Arduino doesn't have ESP32 installed. Install boards manager - esp32 by espressif, select ESP32 Dev Module
*/
// Include the CanSatNeXT library
#include "CanSatNeXT.h"

void setup() {
  // Start the serial line to print data to the terminal
  Serial.begin(115200);
  // Start all CanSatNeXT on-board systems.
  CanSatInit();
}

void loop() {
  // Let's blink the LED
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(400);
}
