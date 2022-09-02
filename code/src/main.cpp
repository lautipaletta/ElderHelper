#include <Arduino.h>
#include "dns_server.h"
#include "utilities.h"
#include "wifi_cfg.h"
#include "telegram_bot.h"

bool dns_cfg_done = false;

void setup() {
  
  Serial.begin(9600);

  INFO_LOADED = check_info_loaded();
  
}

void loop() {

  if(INFO_LOADED){

    if(!is_wifi_connected()){
      connect_to_wifi();
    }

    // Manejo de sensores
    Serial.println("Información Cargada.");
    delay(2000);

  } else {

    if(!dns_cfg_done){
      dns_cfg_done = config_dns_server();
    }

    // Ejecuta Captive Portal si no hay informacion cargada en el JSON
    handle_dns_requests();

  }

}
