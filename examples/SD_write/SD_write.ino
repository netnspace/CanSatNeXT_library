/*
  This example shows the basic way of storing data on the on-board SD-card.
*/

// Include CanSatNeXT functions
#include "CanSatNeXT.h"

// Define our filepath. The / means that it is in the root of the sd-card.
String filepath = "/test.csv";

void setup() {

  // Start the serial 
  Serial.begin(115200);

  // Initialize all on-board systems
  CanSatInit();

  // Here is one example how to write a string to the SD-card.
  uint8_t val = appendFile("/testfile.txt", "THIS IS DATA!\r\n");
}

void loop() {

  // This is one way to store measurements from a sensor
  // Instead of a sensor, let's use random numbers
  uint8_t value = random(255);

  // Since "value" is a number and not a string, we need to convert it
  // before storing
  appendFile(filepath, String(value));

  // After appending the file with our value, let's add a line change
  // so that the file is easier to read
  appendFile(filepath, "\r\n");

  // Note - the same could have been done with appendFile(filepath, String(value) + "\r\n") and many other methods as well, such as using sprintf

  // Finally, let's add a delay of 100 ms before writing again
  delay(100);
}
