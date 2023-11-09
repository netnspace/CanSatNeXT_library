/*
  This code shows how to use the CanSatNeXT on-board IMU (Inertial measurement unit)
  to measure linear and angular acceleration.
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
  float ax, ay, az, gx, gy, gz;
  
  // Call CanSatNeXT functions to read the IMU
  readAcceleration(ax, ay, az);
  readGyro(gx, gy, gz);

  // Let's print the data. There are many variables, so we'll use an advanced way to print it. Regular Serial.print would work as well!
  char report[128];
  memset(report, 0, sizeof(report));
  snprintf(report, sizeof(report), "A: %4.2f %4.2f %4.2f    G: %4.2f %4.2f %4.2f",
      ax, ay, az, gx, gy, gz);
  Serial.println(report);
  
  // Wait 200 milliseconds before doing it again
  delay(200);
}
