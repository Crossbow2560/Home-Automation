#include<ESP8266WiFi.h>
#include<WiFiClientSecure.h>

const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.print("Connected to ");
  Serial.println(ssid);

  WiFiClientSercure client;
  client.setInsecure();
