#include<Arduino.h>
#include <WiFi.h>


//Wifi
#define WIFI_SSID "Dao Nam"
#define WIFI_PASSWORD "18052001"


void initWiFi() { // setup wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}


void setup(){
  Serial.begin(115200);
  initWiFi();
  delay(500);
  
}
void loop() {

  

}