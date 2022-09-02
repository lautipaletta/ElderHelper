#include <Arduino.h>
#include <LittleFS.h>

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
            data += char(file.read());
        }

    }

    file.close();

    LittleFS.end();

    return data;

}