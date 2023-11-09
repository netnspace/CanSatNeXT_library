/*
  This example prints the linear acceleration readings in the correct format for Arduino IDE plotter 
*/
//Include CanSatNeXT library
#include <CanSatNeXT.h>


void setup() {

  // Initialize serial to get data to the terminal
  Serial.begin(115200);

  // Initialize CanSatNeXT systems
  CanSatInit();

}

void loop() {
  // Define variables to hold the IMU data
  float ax, ay, az;
  
  // Call CanSatNeXT functions to read the IMU
  readAcceleration(ax, ay, az);

  // The plotter expects the data to be in format variable1:value1,variable2:value2\r\n.
  // The code below prints the acceleration data in the correct format using Serial.print.

  Serial.print("X:");
  Serial.print(ax, 4);
  Serial.print(",");
  Serial.print("Y:");
  Serial.print(ay, 4);
  Serial.print(",");
  Serial.print("Z:");
  Serial.println(az,4);
  
  // Wait 100 milliseconds before doing it again
  delay(100);
}
