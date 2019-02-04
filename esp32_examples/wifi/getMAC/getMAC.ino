/*
  Get MAC address

  created 1 Nov 2018
  by Pedro Oliveira

*/

#include "esp_system.h"

String getMAC(){
  uint8_t mac[6];
  esp_read_mac(mac, ESP_MAC_WIFI_STA);
  char macStringBuff[18];
  sprintf(macStringBuff, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(macStringBuff);
}

void setup() {
  Serial.begin(115200);
  Serial.println(getMAC());
}

void loop() {
  delay(5000);
  Serial.println(getMAC());
}
