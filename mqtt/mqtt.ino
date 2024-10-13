#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char* kWiFiSSID = "SSID";
const char* kWiFiPassword = "PASSWORD";
// MQTT
const char* kMqttServer = "broker.hivemq.com";
const int kMqttPort = 1883;
const char* kMqttId = "xiao";
const char* kMqttPubTopic = "PUB/TOPIC";
const char* kMqttSubTopic = "SUB/TOPIC";

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0;i < length;i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

WiFiClient esp_client;
PubSubClient client(esp_client);

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(kMqttId))
    {
      Serial.println("connected");
      // connect announcement
      client.publish(kMqttPubTopic, "connect");
      client.subscribe(kMqttSubTopic);
    }
    else
    {
      Serial.printf("failed, rc=%d try again in 5 seconds\n", client.state());
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);

  WiFi.begin(kWiFiSSID, kWiFiPassword);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  client.setServer(kMqttServer, kMqttPort);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  client.publish(kMqttPubTopic, "hello world");
  delay(5000);
}
