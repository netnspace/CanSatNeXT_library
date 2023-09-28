#include "radio.h"

#include <esp_now.h>
#include "esp_wifi.h"
#include <WiFi.h>

esp_now_peer_info_t peerInfo;

uint8_t broadcastAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void internalDataReceivedCallback(const uint8_t * mac, const uint8_t *incomingData, int len);
void internalDataSentCallback(const uint8_t *mac_addr, esp_now_send_status_t status);

bool radioHasBeenInitialized = false;

uint8_t initializeESPNOW(uint8_t *macAddress)
{
    WiFi.mode(WIFI_STA);
    // set receive address
    if(esp_wifi_set_mac(WIFI_IF_STA, &macAddress[0]))
    {
        Serial.println("Invalid MAC address!");
        return 1;
    }

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return 1;
    }

    esp_wifi_set_protocol( WIFI_IF_STA , WIFI_PROTOCOL_LR);   
    esp_now_register_send_cb(internalDataSentCallback);
    esp_now_register_recv_cb(internalDataReceivedCallback);

    // Register peer
    memcpy(peerInfo.peer_addr, macAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return 1;
    }

    memcpy(broadcastAddress, macAddress, 6);

    radioHasBeenInitialized = true;
    return 0;
}

uint8_t sendData(String data)
{   
    if(radioHasBeenInitialized)
    {
        const char *charData = data.c_str();
        return esp_now_send(broadcastAddress, (uint8_t *) charData, data.length());
    }else{
        Serial.println("Radio has not been initialized");
        return 1;
    }
}

uint8_t sendData(char *data, uint16_t len)
{   
    if(radioHasBeenInitialized)
    {
        return esp_now_send(broadcastAddress, (uint8_t *) data, len);
    }else{
        Serial.println("Radio has not been initialized");
        return 1;
    }
}


// This function is called every time data has been sent
void internalDataSentCallback(const uint8_t *mac_addr, esp_now_send_status_t status)
{
    bool success = status == ESP_NOW_SEND_SUCCESS;
    onDataSent(success);
}

// This function is called every time data has been received
void internalDataReceivedCallback(const uint8_t * mac, const uint8_t *incomingData, int len)
{
    String receivedData = "";
    for (int i = 0; i < len; i++) {
        receivedData += (char) incomingData[i];
    }
    onDataReceived(receivedData);
    onBinaryDataReceived(incomingData, len);
}

__attribute__((weak)) void onDataReceived(String data) {
    Serial.print("Received a message: ");
    Serial.print(data);
    Serial.println("");
}

__attribute__((weak)) void onBinaryDataReceived(const uint8_t *data, int len){

}

__attribute__((weak)) void onDataSent(const bool success){

}