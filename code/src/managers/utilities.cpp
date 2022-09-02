#include <Arduino.h>

#include "flash_manager.h"

bool check_info_loaded(){

    String info = flash_read("/user_info.json");

    return info != "";
}