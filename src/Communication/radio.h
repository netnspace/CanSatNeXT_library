// Copyright (c) 2023 Samuli Nyman
// SPDX-License-Identifier: MIT

#ifndef __RADIO_H
#define __RADIO_H

#include "Arduino.h"

uint8_t initializeESPNOW(uint8_t *macAddress);
__attribute__((weak)) void onDataReceived(String data);
__attribute__((weak)) void onBinaryDataReceived(const uint8_t *data, int len);
__attribute__((weak)) void onDataSent(const bool success);

uint8_t sendData(String data);
uint8_t sendData(char *data, uint16_t len);

#endif