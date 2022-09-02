#include <Arduino.h>
#include "dns_server.h"
#include "utilities.h"

void setup() {
  
  Serial.begin(9600);

  config_dns_server();

  info_loaded = check_info_loaded();
  
}

void loop() {

  if(info_loaded){

    // Manejo de sensores
    Serial.println("Información Cargada.");
    delay(2000);

  } else {

    // Ejecuta Captive Portal si no hay informacion cargada en el JSON
    handle_dns_requests();

  }

}