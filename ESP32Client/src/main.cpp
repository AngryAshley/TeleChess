#include <PubSubClient.h>
#include <WiFiManager.h>

const char* mqttServer = "192.168.52.228";
const int mqttPort = 1883;
const char* mqttUser = "telechess";
const char* mqttPassword = "telechess";
const char* mqttTopic = "test";


const char* ssid = "Mikes hotspot";          //  your network SSID (name)
const char* pass = "mikewifi";       // your network password
int status = WL_IDLE_STATUS;


WiFiClient ethClient;
PubSubClient client(ethClient);

void setup() {
  Serial.begin(9600);
  client.setServer(mqttServer, mqttPort);
   status = WiFi.begin(ssid, pass);
  while (status = WL_CONNECTED) {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(ssid, mqttUser, mqttPassword)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(mqttTopic, "hello world");
      // ... and resubscribe
      client.subscribe(mqttTopic);
    } else {
      // if you didn't get a connection to the server:
      Serial.print("failed with state ");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      
    }
    delay(5000);
  }
}


void loop() {
  
}