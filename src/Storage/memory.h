// Copyright (c) 2023 Samuli Nyman
// SPDX-License-Identifier: MIT

#ifndef __SD_H
#define __SD_H

#include "Arduino.h"

uint8_t initSDCard();
bool SDCardPresent();

uint8_t appendFileOnDisk(String path, String data);

template <typename T>
uint8_t appendFile(String path, T data) {
    String dataStr = String(data);
    return appendFileOnDisk(path, dataStr);
}

uint8_t writeFileOnDisk(String path, String data);

template <typename T>
uint8_t writeFile(String path, T data) {
    String dataStr = String(data);
    return writeFileOnDisk(path, dataStr);
}

void printFileSystem();
void newDir(String path);
void deleteDir(String path);
bool fileExists(String path);
uint32_t fileSize(String path);
String readFile(String path);
void renameFile(String oldpath, String newpath);
void deleteFile(String path);

#endif