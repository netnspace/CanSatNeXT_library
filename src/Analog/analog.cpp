// Copyright (c) 2023 Samuli Nyman
// SPDX-License-Identifier: MIT

#include "analog.h"


float calculateVoltageDegree3(int input) {
  float a = -1.907217e-11;
  float b = 8.368612e-08;
  float c = 7.081732e-04;
  float d = 1.572375e-01;

  return a * pow(input, 3) + b * pow(input, 2) + c * input + d;
}

float adcToVoltage(int value)
{
    return calculateVoltageDegree3(value);
}

float analogReadVoltage(int pin)
{
    int value = analogRead(pin);
    return adcToVoltage(value);
}