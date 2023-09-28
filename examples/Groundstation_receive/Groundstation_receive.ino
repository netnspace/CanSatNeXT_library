/*
  This example shows how to use a ground station to receive data from the 
  satellite. The device used for receiving the data can be any ESP32
  board. Usually it is the development board, however it can also be 
  another CanSatNeXT, or any other board with an ESP32 processor.

  The same receive functions also work on the satellite. For sending data
  from the groundstation, please see the example on sending data - it is
  written from satellites perspective, but same functions work on the GS
  as well.
*/

// Include CanSatNeXT library
#include "CanSatNeXT.h"

// This is the address for our groundstation. You can choose this yourself, 
// as long as the setting in satellite and GS match. The address can be ALMOST
// any 6 byte combination. For example 00:00:00:00:00:00 is not valid address.
// The library will tell you if the address you chose is not valid - you can just
// pick another one.
uint8_t groundsationMAC[] = {0xA8, 0x42, 0xE3, 0xDA, 0x86, 0x48};

void setup() {

  // Start serial so that we can print the data. Baud rate here is 115200 symbols/second.
  Serial.begin(115200);

  // Initialize this device as a ground station
  GroundStationInit(groundsationMAC);
}

void loop() {
  // We have nothing to do in the loop.
  delay(1000);
  sendData("THIS IS GS!!");
}

// This is a callback function. It is run every time the radio receives data.
void onDataReceived(String data)
{
  // Let's just print the data
  Serial.println(data);
}

// Tip - the same callback functions can also be used on the satellite

/* There is also a binary callback for those that prefer working with binary data
void onBinaryDataReceived(const uint8_t *data, int len){

}
*/