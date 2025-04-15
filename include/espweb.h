#include <WebSocketsClient.h>
#include <WiFi.h>

const char* ssid = wifissid;
const char* password = wifipass;
const char* serverAddress = addressServer;
const int serverPort = addressPort; 

WebSocketsClient webSocket;

namespace espweb{
    
void setup() {
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {printf(".");}
    Serial.println("\nConnected to WiFi!");

    // Correct WebSocket connection path
    webSocket.begin(serverAddress, serverPort, "/readings", "ws");
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