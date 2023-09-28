#include "CanSatNeXT.h"
#include "Wire.h"


uint8_t CanSatInit() {
  Wire.begin(I2C_SDA, I2C_SCL);

  Serial.println("Init CanSatNeXT!");
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  uint8_t errors = 0;
  if(initIMU())
  {
    Serial.println("Failed to initialize the IMU");
    errors = ERROR_IMU;
  }
  if(initBaro(&Wire))
  {
    Serial.println("Failed to initialize the barometer");
    errors = ERROR_BARO;
  }
  bool sd_present = SDCardPresent();
  if(!sd_present)
  {
    Serial.println("No SD-card present! Can't initialize the memory");
    errors = ERROR_NO_SD_CARD;
  }else if(initSDCard()){
    Serial.println("Failed to initialize the SD-card");
    errors = ERROR_MEMORY;
  }

  return errors;

}


