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

 // Call CanSatNeXT functions to read the IMU
  float ax = readAccelX();
  float ay = readAccelY();
  float az = readAccelZ();
  float gx = readGyroX();
  float gy = readGyroY();
  float gz = readGyroZ();

  // Let's print the data. There are many variables, so we'll use an advanced way to print it. Regular Serial.print would work as well!
  char report[128];
  memset(report, 0, sizeof(report));
  snprintf(report, sizeof(report), "A: %4.2f %4.2f %4.2f    G: %4.2f %4.2f %4.2f",
      ax, ay, az, gx, gy, gz);
  Serial.println(report);
  
  // Wait 200 milliseconds before doing it again
  delay(200);
}
