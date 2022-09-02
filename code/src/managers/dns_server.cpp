#include <Arduino.h>
#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "flash_manager.h"

IPAddress apIP(172, 217, 28, 1);
const byte DNS_PORT = 53;
DNSServer dnsServer;
ESP8266WebServer webServer(80);

extern bool INFO_LOADED;

bool config_dns_server(){

    // Creacion de red wifi NodeMCU (Hotspot)
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("ElderHelper");

    // Levanto servidor DNS para redireccionar peticiones (Captive Portal) 
    dnsServer.start(DNS_PORT, "*", apIP);

    // Index del Captive Portal
    webServer.onNotFound([]() {

        String html_content = flash_read("/index.html");

        webServer.send(200, "text/html", html_content);

    });

    // Cuando recibo POST del index.html (Captive Portal) almaceno la informacion en la Flash y cierro Hotspot
    webServer.on("/dump_info", HTTP_POST, []() {
      
        String ssid = webServer.arg(String("ssid"));
        String password = webServer.arg(String("password"));
        String chat_id = webServer.arg(String("chat_id"));
        
        String info_json = "{\"ssid\":\"" + ssid + "\",\"password\":\"" + password + "\",\"chat_id\":" + chat_id + "}";

        flash_write("/user_info.json", info_json);

        WiFi.mode(WIFI_OFF);

        dnsServer.stop();

        INFO_LOADED = true; // Seteo a 'true' el flag global para que el main.cpp empiece a leer datos de los sensores

    });

    webServer.begin();

    return true;
}

void handle_dns_requests(){
    dnsServer.processNextRequest();
    webServer.handleClient();
}
