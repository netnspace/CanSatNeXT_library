// Copyright (c) 2023 Samuli Nyman
// SPDX-License-Identifier: MIT

#ifndef __RADIO_H
#define __RADIO_H

#include "Arduino.h"

uint8_t initializeESPNOW(uint8_t *macAddress);
void createMacAddress(uint8_t lastByte, uint8_t mac[6]);

__attribute__((weak)) void onDataReceived(String data);
__attribute__((weak)) void onBinaryDataReceived(const uint8_t *data, int len);
__attribute__((weak)) void onDataSent(const bool success);

int8_t getRSSI();

uint8_t sendDataString(String data);         // Sends ASCII data
uint8_t sendData(uint8_t* data, uint16_t len); // Sends binary data

// 1. Basic and easy: ASCII use case (without length)
template <typename T>
uint8_t sendData(T data) {
    String dataStr = String(data);           // Convert to String
    return sendDataString(dataStr);          // Send as ASCII
}

// 2. Binary use case (with length specified)
template <typename T>
uint8_t sendData(T* data, uint16_t len) {
    return sendData(reinterpret_cast<uint8_t*>(data), len); // Send as binary
}

#endif