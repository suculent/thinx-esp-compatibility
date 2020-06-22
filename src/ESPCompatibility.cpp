#include "ESPCompatibility.h"

ESPCompatibility::ESPCompatibility()
{
  this->mac = mac_id();
  this->fcid = flash_id();
}

char *ESPCompatibility::get_mac_id()
{
  uint8_t raw[6];

#ifdef ESP8266
  sprintf(this->mac, "%02X%02X%02X%02X%02X%02X", ESP.getChipID);
#endif

#ifdef ESP32
  esp_read_mac(raw, ESP_MAC_WIFI_STA);
  sprintf(this->mac, "%02X%02X%02X%02X%02X%02X", raw[0], raw[1], raw[2], raw[3], raw[4], raw[5]);
#endif

  return this->mac;
}

char *ESPCompatibility::get_flash_id()
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
}

char *ESPCompatibility::mac_id()
{

  if (this->mac == nullptr)
  {
    this->mac = get_mac_id();
  }

  return this->mac;
}

char *ESPCompatibility::flash_id()
{

  if (this->fcid == nullptr)
  {
    this->fcid = get_flash_id();
  }

  return this->fcid;
}

String ESPCompatibility::mac_id()
{
  return String(mac_id());
}

String ESPCompatibility::flash_id()
{
  return String(flash_id());
}