#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "flash_manager.h"

#define PIN_LED D5

void connect_to_wifi(){

    user_info info = get_user_info();

    Serial.println("SSID: " + info.ssid);
    Serial.println("Password: " + info.password);

    WiFi.begin(info.ssid, info.password);

    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print("*");
        digitalWrite(PIN_LED, !digitalRead(PIN_LED));
    }

    Serial.println("");
    Serial.println("WiFi connection Successful");
    Serial.print("The IP Address of ESP8266 Module is: ");
    Serial.println(WiFi.localIP());// Print the IP address

    digitalWrite(PIN_LED, HIGH);
}

bool is_wifi_connected(){
    return WiFi.status() == WL_CONNECTED;
}
