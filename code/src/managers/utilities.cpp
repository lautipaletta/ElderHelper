#include <Arduino.h>

#include "flash_manager.h"

bool check_info_loaded(){

    String info = flash_read("/user_info.json");

    Serial.println(info);

    if(info == ""){
        return false;
    } else {
        return true;
    }
}