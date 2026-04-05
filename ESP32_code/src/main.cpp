#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// --- Configuration ---
const char* ssid     = "Talv";  // <--- Change this
const char* password = "http200OK";  // <--- Change this
const char* pcIP     = "192.168.1.244";        // <--- Your Windows PC's IP address
const int port       = 4210;                  // Target port
const int sensorPin  = A2;                    // Water sensor on pin A2

WiFiUDP udp;
unsigned long lastSendTime = 0;
const long interval = 3000;

// --- Function Prototypes ---
void connectToWiFi();
void sendUDPMessage(const char* message);

// --- Main Setup ---
void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  connectToWiFi();
}

// --- Main Loop ---
void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastSendTime >= interval) {
    lastSendTime = currentMillis;
    
    int sensorValue = analogRead(sensorPin);
    String message = String(sensorValue);
    
    sendUDPMessage(message.c_str());
    Serial.print("Sensor value sent: ");
    Serial.println(sensorValue);
  }
}

// --- Helper Functions ---

void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void sendUDPMessage(const char* message) {
  udp.beginPacket(pcIP, port);
  udp.print(message);
  udp.endPacket();
}