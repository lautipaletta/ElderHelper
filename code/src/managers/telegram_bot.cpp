#include <Arduino.h>
#include <ArduinoJson.h>

#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#include "flash_manager.h"

bool send_telegram_message(String message) {

    user_info info = get_user_info(); 

    WiFiClientSecure client;

    client.setInsecure();

    String host = "api.telegram.org";

    if (!client.connect(host, 443)) {
        Serial.println("Connection failed");
        return false;
    }

    String url = "/bot5704987969:AAGXeIY0VXaAUaACoqiYibM-mv2Q6sa41hU/sendMessage?chat_id=" + info.chat_id + "&text=" + message;

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

    return true;
}
