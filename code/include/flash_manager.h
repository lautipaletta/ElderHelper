#ifndef flash_manager_h
#define flash_manager_h

#include <Arduino.h>

void flash_write(String filepath, String data);
String flash_read(String filepath);

#endif