#include <Arduino.h>
#include "dns_server.h"
#include "utilities.h"
#include "wifi_cfg.h"
#include "telegram_bot.h"
#include "detectorDeCaidas.h"

#define PIN_LED D5

#define PIN_BTN D3
#define TIEMPO_REBOTE 100
bool btnEstaApretado = false;
int millisEnUltimoApretado = 0;
void managerBtn();

bool dns_cfg_done = false;

void setup() {
  Serial.begin(9600);

  INFO_LOADED = check_info_loaded();

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BTN, INPUT_PULLUP);
}

void loop() {

  if(INFO_LOADED){

    if(!is_wifi_connected()){
      connect_to_wifi();
    }

    // Manejo de sensores
    managerBtn();
    
    if (dispositivoEnEstadoCaida()) send_telegram_message("El dispositivo ha detectado una caida");

    delay(15);

  } else {

    if(!dns_cfg_done){
      dns_cfg_done = config_dns_server();
    }

    // Ejecuta Captive Portal si no hay informacion cargada en el JSON
    handle_dns_requests();

  }

}

void managerBtn() {
    if (digitalRead(PIN_BTN) == LOW && !btnEstaApretado && millis() - millisEnUltimoApretado > TIEMPO_REBOTE) {
       send_telegram_message("¡Se ha presionado el botón de SOS!"); 
       millisEnUltimoApretado = millis();
       btnEstaApretado = true;
    }
    if (digitalRead(PIN_BTN) == HIGH) btnEstaApretado = false;
} 
