#include <Arduino.h>
#include <ArduinoJson.h>

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include "flash_manager.h"

bool send_telegram_message(String message) {
    JsonObject obj = get_user_info(); 

    String chat_id = obj[String("chat_id")];

    WiFiClient client;
    HTTPClient http;

    String request = "https://api.telegram.org/bot{}/sendMessage?chat_id=" + chat_id + "&text=" message;

    http.begin(client, request.c_str());

    return http.GET() > 0;
}
