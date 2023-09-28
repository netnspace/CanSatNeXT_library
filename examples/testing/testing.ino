#include <CanSatNeXT.h>

void setup() {
  // put your setup code here, to run once:
  CanSatInit();

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(100);
  float x,y,z;
  readAcceleration(x,y,z);

}
