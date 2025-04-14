#include <WebSocketsClient.h>
#include <WiFi.h>

const char* ssid = wifissid;
const char* password = wifipass;
// 192.168.100.223
const char* serverAddress = addressServer;
const int serverPort = addressPort; 

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_CONNECTED:
      Serial.println("Connected to WebSocket Server!");
      break;
    case WStype_TEXT:
      Serial.printf("Received from Server: %s\n", payload);
      break;
    case WStype_DISCONNECTED:
      Serial.println("Disconnected from WebSocket Server!");
      break;
  }
}

namespace espweb{
    
void setup() {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");

    // Correct WebSocket connection path
    webSocket.begin(serverAddress, serverPort, "/readings", "ws");
    webSocket.onEvent(webSocketEvent);
    }


void send(float heightValue, float tempValue, float heartRate, int spO2, float weightValue, float bmiValue) {
    

    if (webSocket.isConnected()) {
        String json = "{";
        json += "\"height\": " + String(heightValue, 2) + ",";
        json += "\"weight\": " + String(weightValue, 2) + ",";
        json += "\"BMI\": " + String(bmiValue, 2) + ",";
        json += "\"bodyTemperature\": " + String(tempValue, 2) + ",";
        json += "\"pulseRate\": " + String(heartRate, 2) + ",";
        json += "\"bloodOxygenLevel\": " + String(spO2);
        json += "}";

        webSocket.sendTXT(json);
    }
}

    }