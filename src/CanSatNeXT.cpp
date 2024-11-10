// Copyright (c) 2023 Samuli Nyman
// SPDX-License-Identifier: MIT

#include "CanSatNeXT.h"
#include "Wire.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"



uint8_t CanSatInit(uint8_t maccAddressLastByte){
  uint8_t address[6];
  createMacAddress(maccAddressLastByte, address);
  return CanSatInit(address);
}

uint8_t CanSatInit(uint8_t *macAddress) {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //This disables input voltage checks - enabling the satellite to use batteries until they are empty

  Wire.begin(I2C_SDA, I2C_SCL);

  Serial.println("Init CanSatNeXT!");
  pinMode(LED, OUTPUT);
  pinMode(MEAS_EN, OUTPUT);
  pinMode(SD_DET, INPUT);
  digitalWrite(LED, HIGH);
  digitalWrite(MEAS_EN, HIGH);
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
  if(initSDCard()){
    Serial.println("Failed to initialize the SD-card");
    errors = ERROR_MEMORY;
  }

  // As a safety feature, initialize radio only if macAddress is provided
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

uint8_t GroundStationInit(uint8_t maccAddressLastByte){
  uint8_t address[6];
  createMacAddress(maccAddressLastByte, address);
  return GroundStationInit(address);
}

uint8_t GroundStationInit(uint8_t *macAddress) {
  if(initializeESPNOW(macAddress))
  {
    Serial.println("Failed to initialize the radio system");
    return ERROR_RADIO;
  }

  return 0;
}


