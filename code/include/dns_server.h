#ifndef dns_server_h
#define dns_server_h

#include <Arduino.h>

void config_dns_server();
void handle_dns_requests();
bool info_loaded;

#endif