#ifndef __IMU_H
#define __IMU_H

#include "Arduino.h"

uint8_t readAcceleration(float &x, float &y, float &z);
uint8_t readGyro(float &x, float &y, float &z);
uint8_t initIMU();

#endif