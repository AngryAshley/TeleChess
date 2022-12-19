#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "12connect";
const char* password = "";

const uint16_t port = 1100;
const char * host = "217.105.47.86";

WiFiClient client;
WiFiServer wifiServer(port);

void setup() {

  Serial.begin(9600);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  while(!client.connect(host, port)) 
  {
   Serial.println("Connection to host failed");
 
   delay(1000);
  }
  delay(1000);
  client.print("thijs");
}

void loop() {

  if(client.available())
  {
    Serial.println(client.readString());
  }
}
