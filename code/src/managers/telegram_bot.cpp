#include <Arduino.h>
#include <ArduinoJson.h>

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include "flash_manager.h"

bool send_telegram_message(String message) {

    user_info info = get_user_info(); 

    WiFiClient client;
    HTTPClient http;

    String request = "https://api.telegram.org/bot5704987969:AAGXeIY0VXaAUaACoqiYibM-mv2Q6sa41hU/sendMessage?chat_id=" + info.chat_id + "&text=" + message;

    http.begin(client, request.c_str());

    return http.GET() > 0;
}
