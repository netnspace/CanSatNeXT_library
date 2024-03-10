// Copyright (c) 2023 Samuli Nyman
// SPDX-License-Identifier: MIT

#ifndef __IMU_H
#define __IMU_H

#include "Arduino.h"

uint8_t readAcceleration(float &x, float &y, float &z);
uint8_t readGyro(float &x, float &y, float &z);
uint8_t initIMU();

float readAccelX();
float readAccelY();
float readAccelZ();
float readGyroX();
float readGyroY();
float readGyroZ();

#endif