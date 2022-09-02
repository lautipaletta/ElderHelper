#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

#include "flash_manager.h"

void connect_to_wifi(String ssid, String password){

    Serial.println("SSID: " + ssid);
    Serial.println("Password: " + password);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print("*");
    }

    Serial.println("");
    Serial.println("WiFi connection Successful");
    Serial.print("The IP Address of ESP8266 Module is: ");
    Serial.println(WiFi.localIP());// Print the IP address

}