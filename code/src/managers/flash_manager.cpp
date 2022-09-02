#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include "flash_manager.h"

void flash_write(String filepath, String data){

    if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
    } 

    File file = LittleFS.open(filepath, "w");

    file.print(data);
    delay(1);

    file.close();

    LittleFS.end();

    return;

}

String flash_read(String filepath){

    if(!LittleFS.begin()){
        Serial.println("An Error has occurred while mounting LittleFS");
    }

    File file = LittleFS.open(filepath, "r");

    String data = "";

    if(!file){

        Serial.println("Error, file not found.");

    } else {

        while(file.available()){
            data += (char)file.read();
        }

    }

    file.close();

    LittleFS.end();

    return data;
}

user_info get_user_info() {
    
    DynamicJsonDocument doc(1024);

    String user_data = flash_read("/user_info.json");

    deserializeJson(doc, user_data);

    JsonObject obj = doc.as<JsonObject>();

    user_info info;

    info.ssid = (String)obj[String("ssid")];
    info.password = (String)obj[String("password")];
    info.chat_id = (String)obj[String("chat_id")];

    return info;
}
