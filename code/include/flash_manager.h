#ifndef flash_manager_h
#define flash_manager_h

#include <Arduino.h>
#include <ArduinoJson.h>

void flash_write(String filepath, String data);
String flash_read(String filepath);
JsonObject get_user_info();

#endif
