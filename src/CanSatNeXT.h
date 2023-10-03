// Copyright (c) 2023 Samuli Nyman
// SPDX-License-Identifier: MIT

#ifndef CANSAT_H
#define CANSAT_H

#include "Sensors/imu.h"
#include "Sensors/baro.h"
#include "Storage/memory.h"
#include "CanSatNeXTPins.h"
#include "Communication/radio.h"
#include "Analog/analog.h"

#define NO_ERROR 0
#define ERROR_IMU 1
#define ERROR_BARO 2
#define ERROR_RADIO 3
#define ERROR_MEMORY 4
#define ERROR_NO_SD_CARD 5

uint8_t CanSatInit(uint8_t *macAddress = nullptr);
uint8_t GroundStationInit(uint8_t *macAddress);

#endif