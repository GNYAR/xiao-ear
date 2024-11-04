#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#include <WiFi.h>
#include <PubSubClient.h>

#define RESULT_COUNT 3

// WiFi
const char* kWiFiSSID = "SSID";
const char* kWiFiPassword = "PASSWORD";
// MQTT
const char* kMqttServer = "broker.hivemq.com";
const int kMqttPort = 1883;
const char* kMqttId = "xiao_oled";
const char* kMqttTopic = "TOPIC";

WiFiClient esp_client;
PubSubClient client(esp_client);

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

// kws result mapping
const char* mapping[RESULT_COUNT] = {
  "",
  "好",
  "不",
};

void ConnectMqtt() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(kMqttId)) {
      Serial.println("connected");
      // connect announcement
      client.publish(kMqttTopic, "xiao_oled connect");
      client.subscribe(kMqttTopic);
    }
    else {
      Serial.printf("failed, rc=%d try again in 5 seconds\n", client.state());
      delay(5000);
    }
  }
}

void Display(const char* str)
{
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print(str);
  u8g2.sendBuffer();
}

void CallbackMqtt(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  int n = 0;
  for (int i = 0;i < length;i++)
  {
    int x = (char)payload[i] - '0';
    if (-1 < x and x < 10)
    {
      if (n != 0) n *= 10;
      n += x;
    }
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if (-1 < n and n < RESULT_COUNT) Display(mapping[n]);
}

void setup(void) {
  Serial.begin(115200);
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_unifont_t_chinese1);
  u8g2.setFontDirection(0);

  WiFi.begin(kWiFiSSID, kWiFiPassword);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Display("Connecting to WiFi...");
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  client.setServer(kMqttServer, kMqttPort);
  client.setCallback(CallbackMqtt);

  Display("Device ready.");
}

void loop(void) {
  if (!client.connected())
  {
    ConnectMqtt();
  }
  client.loop();
}
