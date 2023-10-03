// Copyright (c) 2023 Samuli Nyman
// SPDX-License-Identifier: MIT

#ifndef __ANALOG_H
#define __ANALOG_H

#include "Arduino.h"


float adcToVoltage(int value);
float analogReadVoltage(int pin);

#endif