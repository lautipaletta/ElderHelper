#ifndef flash_manager_h
#define flash_manager_h

#include <Arduino.h>
#include <ArduinoJson.h>

struct user_info
{
    String ssid;
    String password;
    String chat_id;
};

void flash_write(String filepath, String data);
String flash_read(String filepath);
user_info get_user_info();

#endif
