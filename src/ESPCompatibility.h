#include <Arduino.h>

class ESPCompatibility {

  private:

    char * mac = nullptr;
    char * fcid = nullptr;

    char * get_mac_id();
    char * get_flash_id();

  public:

    // Base Functionality

    char* mac_id();
    char* flash_id();

    // Convenience Getters

    String mac_id();
    String flash_id();

}