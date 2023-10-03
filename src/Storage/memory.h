// Copyright (c) 2023 Samuli Nyman
// SPDX-License-Identifier: MIT

#ifndef __SD_H
#define __SD_H

#include "Arduino.h"

uint8_t initSDCard();
bool SDCardPresent();
uint8_t appendFile(String filename, String data);
void printFileSystem();
void newDir(String path);
void deleteDir(String path);
uint8_t fileExists(String path);
uint32_t fileSize(String path);
void writeFile(String path, String data);
String readFile(String path);
void renameFile(String oldpath, String newpath);
void deleteFile(String path);

#endif