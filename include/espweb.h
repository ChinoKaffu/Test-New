#include <WebSocketsClient.h>
#include <WiFi.h>

const char* ssid = wifissid;
const char* password = wifipass;
// 192.168.100.223

const char* serverAddress = "192.168.1.12";
const int serverPort = 4000; 

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
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");

    // Correct WebSocket connection path
    webSocket.begin(serverAddress, serverPort, "/readings", "ws");
    webSocket.onEvent(webSocketEvent);
    }


    void loop() {

    webSocket.loop();

    if (webSocket.isConnected()) {  // Only send if connected
        String json = "{\"dog_style\": " + String(69) + "}";
        webSocket.sendTXT(json);
        delay(2000);
    }
    }
}