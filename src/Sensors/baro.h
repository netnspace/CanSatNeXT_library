// Copyright (c) 2023 Samuli Nyman
// SPDX-License-Identifier: MIT

#ifndef __BARO_H
#define __BARO_H

#include "Arduino.h"
#include "Wire.h"

float readPressure();
float readTemperature();
uint8_t initBaro(TwoWire *wire);

#endif