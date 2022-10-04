#include <PubSubClient.h>
#include <WiFiManager.h>

const char *mqttServer = "192.168.52.228";
const int mqttPort = 1883;
const char *mqttUser = "telechess";
const char *mqttPassword = "telechess";
const char *mqttTopic = "test";

const char *ssid = "Mikes hotspot"; //  your network SSID (name)
const char *pass = "mikewifi";      // your network password
int status = WL_IDLE_STATUS;

WiFiClient ethClient;
PubSubClient client(ethClient);

void setup()
{
  Serial.begin(9600);
  client.setServer(mqttServer, mqttPort);
  status = WiFi.begin(ssid, pass);
}

void callback(char *topic, byte *message, unsigned int length)
{
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();
}
void loop()
{
  if (status = WL_CONNECTED)
  {
    client.connect(ssid, mqttUser, mqttPassword);
    // if you get a connection, report back via serial:
    if (client.connected())
    {
      // Once connected, publish an announcement
      // ... and resubscribe
      client.subscribe(mqttTopic);  
      client.setCallback(callback);
  
    }
    else
    {
      // if you didn't get a connection to the server:
      Serial.print("failed with state ");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
    }
    client.loop();
  
  }
}