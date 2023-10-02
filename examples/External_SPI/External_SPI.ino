/*
  This example shows how to use the SPI from the extension header to connect to an
  external SPI device. Essentially, it is used just like normally. The pins just
  need to be modified based on the hardware setup. This example uses an external
  analog-to-digital converter MCP3008, but the same approach works for any other SPI
  device as well. This example uses Adafruit MCP3008 library to communicate with the MCP3008.
  The code is modified from the Adafruit example provided with the library.
*/

#include <Adafruit_MCP3008.h>

// Include CanSatNeXT to get the pin definitions
#include <CanSatNeXT.h>

Adafruit_MCP3008 adc;

int count = 0;


void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("MCP3008 simple test.");

  // Hardware SPI (specify CS, use any available digital)
  // Can use defaults if available, ex: UNO (SS=10) or Huzzah (SS=15)
  
 /* *'''''''''''''''''
 This is the only modification to the library example
 */
  // Use SPI pins. Chip select can be any GPIO pin, this time we use pin 12.
  adc.begin(SPI_CLK, SPI_MOSI, SPI_MISO, 12);
// ^^^^^^^^^^^^^^

  // Feather 32u4 (SS=17) or M0 (SS=16), defaults SS not broken out, must specify
  //adc.begin(10);  

  // Software SPI (specify all, use any available digital)
  // (sck, mosi, miso, cs);
  //adc.begin(13, 11, 12, 10);
}


void loop() {
  for (int chan=0; chan<8; chan++) {
    Serial.print(adc.readADC(chan)); Serial.print("\t");
  }
  Serial.print("["); Serial.print(count); Serial.println("]");
  count++;
  
  delay(100);
}
