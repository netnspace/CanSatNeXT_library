/*
  This example shows how data can be sent from the satellite to the groundstation. The same functions work the other way around as well, and can be used to send data to the satellite from the groundstation.

  Caution - You should always have an antenna in a radio system before transmitting anything. Make sure the antenna is plugged in before sending data via the radio.
*/

#include "CanSatNeXT.h"

void setup() {

  // Initialize serial with baud rate 115200
  Serial.begin(115200);

  // Initialize CanSatNeXT systems. Calling this function with an address as a parameter enables the radio. The address is shared by both the transmitter and receiver. 
  CanSatInit(72);
}

void loop() {
  
  // Let's use a random number to mock a sensor
  uint8_t value = random(255);

  // The data can be sent either as a string or as binary data.

  // Send a simple message
  sendData("This is our message.");

  // To send a variable, we need to convert it into a string
  sendData(String(value));

  // Alternatively, we can send the value as binary data. This is more efficient, but can be tricky.
  char msg[1];
  msg[0] = value;
  sendData(msg, sizeof(msg));
  
  
  delay(1000);
}