// Copyright (c) 2023 Samuli Nyman
// SPDX-License-Identifier: MIT

#include "radio.h"
#include <esp_now.h>
#include "esp_wifi.h"
#include <WiFi.h>

#define ESP_MAJOR_VERSION 3

#if defined(ESP_ARDUINO_VERSION)
  #define ESP_MAJOR_VERSION ESP_ARDUINO_VERSION >> 16
#endif

uint8_t radio_channel = 1; // Default channel set to 1 (2.412 GHz)
esp_now_peer_info_t peerInfo;

uint8_t broadcastAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#if ESP_MAJOR_VERSION == 3
void internalDataReceivedCallback(const esp_now_recv_info *info, const uint8_t *data, int data_len);
#else
void internalDataReceivedCallback(const uint8_t * mac, const uint8_t *incomingData, int len);
#endif
void internalDataSentCallback(const uint8_t *mac_addr, esp_now_send_status_t status);
void promiscuous_rx_cb(void *buf, wifi_promiscuous_pkt_type_t type);

bool radioHasBeenInitialized = false;


typedef struct {
  unsigned frame_ctrl: 16;
  unsigned duration_id: 16;
  uint8_t addr1[6]; /* receiver address */
  uint8_t addr2[6]; /* sender address */
  uint8_t addr3[6]; /* filtering address */
  unsigned sequence_ctrl: 16;
  uint8_t addr4[6]; /* optional */
} wifi_ieee80211_mac_hdr_t;

typedef struct {
  wifi_ieee80211_mac_hdr_t hdr;
  uint8_t payload[0]; /* network data ended with 4 bytes csum (CRC32) */
} wifi_ieee80211_packet_t;

void setRadioChannel(uint8_t newChannel)
{
    // Ensure channel is within the allowed range (1-11) 2.407 GHz + channel * 0.05 Ghz, up to 11.

    if(newChannel > 11) newChannel = 11;
    radio_channel = newChannel;
}

uint8_t getRadioChannel()
{
    uint8_t primary_channel;
    wifi_second_chan_t secondary_channel;
    esp_err_t get_channel_result = esp_wifi_get_channel(&primary_channel, &secondary_channel);

    if (get_channel_result == ESP_OK) {
        return primary_channel;
    } else {
        return 0;
    }
}

void printRadioFrequency()
{
    uint8_t channel = getRadioChannel();
    if(channel == 0)
    {
        Serial.println("Error when fetching frequency");
    }else{
        float frequency = 2.407 + channel * 0.005;
        char report[128];
        memset(report, 0, sizeof(report));
        snprintf(report, sizeof(report), "Radio frequency: %.3f GHz", frequency);
        Serial.println(report);
    }
}



void printAddress(uint8_t mac[6])
{
  for (int n = 0; n < 6; n++)
  {
    Serial.print(((uint8_t) mac[n]) < 16 ? "0" : "");
    Serial.print(mac[n], HEX);
    Serial.print(n < 5 ? ":" : "");
  }
  Serial.println();
}

uint8_t initializeESPNOW(uint8_t *macAddress)
{
    memcpy(broadcastAddress, macAddress, 6);
    
    WiFi.mode(WIFI_STA);
    // set receive address
    if(esp_wifi_set_mac(WIFI_IF_STA, broadcastAddress))
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
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb(&promiscuous_rx_cb);

    // Register peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return 1;
    }

    uint8_t new_channel = radio_channel;
    esp_err_t set_channel_result = esp_wifi_set_channel(new_channel, WIFI_SECOND_CHAN_NONE);
    if (set_channel_result != ESP_OK) {
        Serial.println("Failed to set Wi-Fi channel.");
    }


    radioHasBeenInitialized = true;

    return 0;
}

void createMacAddress(uint8_t lastByte, uint8_t mac[6]) 
{
    mac[0] = 0x02;
    mac[1] = 0x2A;
    mac[2] = 0x56;
    mac[3] = 0x72;
    mac[4] = 0x2B;
    mac[5] = lastByte;
}

uint8_t sendDataString(String data)
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

uint8_t sendData(uint8_t *data, uint16_t len)
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

#if ESP_MAJOR_VERSION == 3
void internalDataReceivedCallback(const esp_now_recv_info *info, const uint8_t *data, int data_len) {
    const uint8_t *mac = info->src_addr;
    String receivedData = "";
    for (int i = 0; i < data_len; i++) {
        receivedData += (char) data[i];
    }
    onDataReceived(receivedData);
    onBinaryDataReceived(data, data_len);
}
#else
void internalDataReceivedCallback(const uint8_t * mac, const uint8_t *incomingData, int len)
{
    String receivedData = "";
    for (int i = 0; i < len; i++) {
        receivedData += (char) incomingData[i];
    }
    onDataReceived(receivedData);
    onBinaryDataReceived(incomingData, len);
}
#endif


int8_t lastRSSI = 1;
int8_t getRSSI(){
    return lastRSSI;
}

void promiscuous_rx_cb(void *buf, wifi_promiscuous_pkt_type_t type) {
  if (type != WIFI_PKT_MGMT)
    return;

  const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t *)buf;
  const wifi_ieee80211_packet_t *ipkt = (wifi_ieee80211_packet_t *)ppkt->payload;
  const wifi_ieee80211_mac_hdr_t *hdr = &ipkt->hdr;
  // record RSSI only if the MAC address matches
  if (memcmp(broadcastAddress, hdr->addr2, 6) == 0) {
    int8_t rssi = ppkt->rx_ctrl.rssi;
    lastRSSI = rssi;
  }
}

// This function is called every time data has been received
__attribute__((weak)) void onDataReceived(String data) {
}

__attribute__((weak)) void onBinaryDataReceived(const uint8_t *data, uint16_t len){
}

__attribute__((weak)) void onDataSent(const bool success){

}