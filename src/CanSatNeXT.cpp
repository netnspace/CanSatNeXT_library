#include "CanSatNeXT.h"
#include "Wire.h"


uint8_t CanSatInit(uint8_t *macAddress) {
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

  // As a safety feature, initialize radio if macAddress is provided
  if(macAddress != nullptr)
  {
    if(initializeESPNOW(macAddress))
    {
      Serial.println("Failed to initialize the radio system");
      errors = ERROR_RADIO;
    }
  }

  return errors;

}

uint8_t GroundStationInit(uint8_t *macAddress) {
  if(initializeESPNOW(macAddress))
  {
    Serial.println("Failed to initialize the radio system");
    return ERROR_RADIO;
  }

  return 0;
}


