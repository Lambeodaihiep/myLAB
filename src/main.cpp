#include "Arduino.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PWMServoDriver.h>
#include "..\.pio\libdeps\websocket.cpp"
#include "..\.pio\libdeps\wifi_and_SPIFFS.cpp"
#include "..\.pio\libdeps\PCA9685.cpp"

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  initSPIFFS();
  
  // Load values saved in SPIFFS
  ssid = readFile(SPIFFS, ssidPath);
  pass = readFile(SPIFFS, passPath);
  ip = readFile(SPIFFS, ipPath);
  gateway = readFile (SPIFFS, gatewayPath);
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(ip);
  Serial.println(gateway);

  if(initWiFi()) {
    initWebSocket();

    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/index.html", "text/html");
    });

    server.serveStatic("/", SPIFFS, "/");
    
    // Route to load style.css file
    server.on("/index.css", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/index.css", "text/css");
    });

    server.begin();

    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates

    Homming();
    delay(2000);
    Serial.println("You can start 12 channel Servo test!");
  }
  else {
    // Connect to Wi-Fi network with SSID and password
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
    WiFi.softAP("ESP-WIFI-MANAGER", NULL);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP); 

    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/wifi_manager.html", "text/html");
    });
    
    server.serveStatic("/", SPIFFS, "/");
    
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
      int params = request->params();
      for(int i=0;i<params;i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->isPost()){
          // HTTP POST ssid value
          if (p->name() == PARAM_INPUT_1) {
            ssid = p->value().c_str();
            Serial.print("SSID set to: ");
            Serial.println(ssid);
            // Write file to save value
            writeFile(SPIFFS, ssidPath, ssid.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_INPUT_2) {
            pass = p->value().c_str();
            Serial.print("Password set to: ");
            Serial.println(pass);
            // Write file to save value
            writeFile(SPIFFS, passPath, pass.c_str());
          }
          // HTTP POST ip value
          if (p->name() == PARAM_INPUT_3) {
            ip = p->value().c_str();
            Serial.print("IP Address set to: ");
            Serial.println(ip);
            // Write file to save value
            writeFile(SPIFFS, ipPath, ip.c_str());
          }
          // HTTP POST gateway value
          if (p->name() == PARAM_INPUT_4) {
            gateway = p->value().c_str();
            Serial.print("Gateway set to: ");
            Serial.println(gateway);
            // Write file to save value
            writeFile(SPIFFS, gatewayPath, gateway.c_str());
          }
          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      request->send(200, "text/plain", "Done. ESP will restart, connect to your router and go to IP address: " + ip);
      delay(3000);
      ESP.restart();
    });
    server.begin();
  }
}

void loop() {
  if (newRequest){
    Serial.print(message);
    int i = servoIndex.toInt();
    Serial.print(i);
    Serial.println(continuum[i]);
    if(continuum[i] < position.toInt()) {
      for(continuum[i]; continuum[i] < position.toInt(); continuum[i]++) {
        pwm.setPWM(i, 0, angleToPulse(continuum[i], bias[i]));
        delay(25);
      }
    }
    else {
      for(continuum[i]; continuum[i] > position.toInt(); continuum[i]--) {
        pwm.setPWM(i, 0, angleToPulse(continuum[i], bias[i]));
        delay(25);
      }
    }
    newRequest = false;
  }
  else {
    for(int i = 0; i < 12; i++) {
      pwm.setPWM(i, 0, angleToPulse(continuum[i], bias[i]));
    }
    ws.cleanupClients();
  }
  
}