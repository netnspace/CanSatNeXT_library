// Copyright (c) 2023 Samuli Nyman
// SPDX-License-Identifier: MIT

#include "CanSatNeXTPins.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

SPIClass spi = SPIClass(VSPI);

uint8_t initSDCard()
{
    pinMode(SD_DET, INPUT);
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, LOW);
    spi.begin(SPI_CLK, SPI_MISO, SPI_MOSI, SD_CS);

    if (!SD.begin(SD_CS,spi,80000000)) return 1;
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return 1;
    }

    return 0;
}

uint8_t appendFileOnDisk(String path, String data)
{
    File file = SD.open(path, FILE_APPEND);
    if(!file){
        return 1;
    }
    uint8_t error = file.print(data);
    file.close();
    if(error) return 1;
    return 0;
}

void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry = dir.openNextFile();
    if (!entry) {
      // No more files in the directory
      break;
    }
    Serial.print("|");
    for (int i = 0; i < numTabs; i++) {
      Serial.print("__");
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      Serial.println();
    }
    entry.close();
  }
}

void printFileSystem() {
  Serial.println("root");
  File root = SD.open("/");
  if (root) {
    printDirectory(root, 1);
    root.close();
  } else {
    Serial.println("Failed to open directory");
  }
}

void newDir(String path) {
    SD.mkdir(path);
}

void deleteDir(String path)
{
    SD.rmdir(path);
}

bool fileExists(String path)
{
    return SD.exists(path);
}

uint32_t fileSize(String path)
{
    File f = SD.open(path);
    if(!f) return 0;
    uint32_t length = f.size();
    f.close();
    return length;
}

uint8_t writeFileOnDisk(String path, String data)
{
    File file = SD.open(path, FILE_WRITE);
    if(!file){
        return 1;
    }
    uint8_t error = file.print(data);
    file.close();
    if(error) return 1;
    return 0;
}

String readFile(String path)
{
    File f = SD.open(path);
    if(!f) return "";

    String s = f.readString();
    f.close();
    return s;
}

void renameFile(String oldpath, String newpath)
{
    SD.rename(oldpath, newpath);
}

void deleteFile(String path)
{
    SD.remove(path);
}

bool SDCardPresent()
{
    return digitalRead(SD_DET) == 0;
}