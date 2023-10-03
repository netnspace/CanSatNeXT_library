// Copyright (c) 2023 Samuli Nyman
// SPDX-License-Identifier: MIT

#include "imu.h"
#include "Arduino.h"
#include "LSM6.h"

LSM6 imu;

uint8_t initIMU()
{
    if (!imu.init(LSM6::device_DS33,LSM6::sa0_low))
    {
        Serial.println("Failed to detect and initialize IMU!");
        return 1;
    } 
    imu.enableDefault();
    return 0;
}

uint8_t readAcceleration(float &x, float &y, float &z){
  imu.read();
  x = imu.a.x * 0.061 * 0.001;
  y = imu.a.y * 0.061 * 0.001;
  z = imu.a.z * 0.061 * 0.001;
  return 0;
}

uint8_t readGyro(float &x, float &y, float &z){
  imu.read();
  x = imu.g.x * 8.75 * 0.001;
  y = imu.g.y * 8.75 * 0.001;
  z = imu.g.z * 8.75 * 0.001;
  return 0;
}