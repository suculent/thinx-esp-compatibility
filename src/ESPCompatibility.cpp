#include "ESPCompatibility.h"

ESPCompatibility::ESPCompatibility()
{
  this->mac = mac_id();
  this->fcid = flash_id();
}

char * ESPCompatibility::get_mac_id()
{
  uint8_t raw[6];

  /*
  uint32_t mac0 = MAC0;
  uint32_t mac1 = MAC1;
  uint32_t chipid = CHIPID;
  uint32_t apiChipId = ESP.getChipId();
  String macAddress = WiFi.macAddress();
  Serial.printf("mac0 =       0x%08x\n", mac0);
  Serial.printf("mac1 =       0x%08x\n", mac1);
  Serial.printf("chipid =     0x%08x\n", chipid);
  Serial.printf("apiChipId =  0x%08x\n", apiChipId);
  Serial.printf("macaddress = %s\n", macAddress.c_str());
  */

#ifdef ESP8266
  uint32_t chipid = ESP.getChipId();
  sprintf(this->mac, "5CCF7F%.6X", ESP.getChipId());
#endif

#ifdef ESP32
  esp_read_mac(raw, ESP_MAC_WIFI_STA);
  sprintf(this->mac, "%02X%02X%02X%02X%02X%02X", raw[0], raw[1], raw[2], raw[3], raw[4], raw[5]);
#endif

  String macAddress = WiFi.macAddress();
  macAddress.replace(":", "");
  macAddress.replace(" ", "");
  sprintf(this->mac, "%s", macAddress.c_str());

  return this->mac;
}

char * ESPCompatibility::get_flash_id()
{
  uint8_t raw[6];

#ifdef ESP8266
  sprintf(this->fcid, "%02X%02X%02X", ESP.getFlashChipID);
#endif

#ifdef ESP32
  esp_read_mac(raw, ESP_MAC_WIFI_STA); // getFlashChipID not supported on ESP32 so far
  sprintf(this->fcid, "%02X%02X%02X", raw[3], raw[4], raw[5]);
#endif

  return this->fcid;
}

char *ESPCompatibility::mac_id()
{
  if (this->mac == nullptr)
  {
    this->mac = get_mac_id();
  }
  return this->mac;
}

char * ESPCompatibility::flash_id()
{
  if (this->fcid == nullptr)
  {
    this->fcid = get_flash_id();
  }
  return this->fcid;
}