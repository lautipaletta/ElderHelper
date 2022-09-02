#ifndef dns_server_h
#define dns_server_h

#include <Arduino.h>

bool config_dns_server();
void handle_dns_requests();
bool INFO_LOADED;

#endif