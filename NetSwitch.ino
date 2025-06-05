#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi credentials
const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

// MQTT server details
const char* mqtt_server = "YOUR_BROKER_IP";

// Pins for light and fan
const int lightPin = D5;
const int fanPin = D2;

// WiFi and MQTT client objects
WiFiClient espClient;
PubSubClient client(espClient);

// MQTT callback function
void callback(char* topic, byte* payload, unsigned int length) {
    String message = "";
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }

    Serial.printf("Received message on topic %s: %s\n", topic, message.c_str());

    if (String(topic) == "room/light/main") {
        digitalWrite(lightPin, (message == "ON") ? LOW : HIGH);
    } else if (String(topic) == "room/fan") {
        digitalWrite(fanPin, (message == "ON") ? HIGH : LOW);
    }
}

// Reconnect to MQTT broker
void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP8266Client")) {
            Serial.println("connected");
            client.subscribe("room/light/main");
            client.subscribe("room/fan");
        } else {
            Serial.printf("failed, rc=%d. Retrying in 5 seconds...\n", client.state());
            delay(5000);
        }
    }
}

void setup() {
    // Initialize pins
    pinMode(lightPin, OUTPUT);
    pinMode(fanPin, OUTPUT);

    // Start serial communication
    Serial.begin(115200);

    // Connect to WiFi
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");

    // Configure MQTT client
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop() {
    // Ensure MQTT connection
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}


// Upload the code to your ESP8266 board using the Arduino IDE.
