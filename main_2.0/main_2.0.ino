#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "env.h"

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 5
#define DHTTYPE DHT22 
DHT_Unified dht(DHTPIN, DHTTYPE);

// WiFi credentials
const char WIFI_SSID[] = "****";
const char WIFI_PASSWORD[] = "****";

// Device name from AWS
const char THINGNAME[] = "ESP8266";

// MQTT broker host address from AWS
const char MQTT_HOST[] = "armxa1cuqcv3k-ats.iot.us-east-2.amazonaws.com";

// MQTT topics
const char AWS_IOT_PUBLISH_TOPIC[] = "esp8266/pub";
const char AWS_IOT_SUBSCRIBE_TOPIC[] = "esp8266/sub";

// Publishing interval
const long interval = 5000;

// Timezone offset from UTC
const int8_t TIME_ZONE = -5;

// WiFiClientSecure object for secure communication
WiFiClientSecure net;

// X.509 certificate for the CA
BearSSL::X509List cert(cacert);

// X.509 certificate for the client
BearSSL::X509List client_crt(client_cert);

// RSA private key
BearSSL::PrivateKey key(privkey);

// MQTT client instance
PubSubClient client(net);

// LED indication
const int ledpin1 = 14;
const int ledpin2 = 12;
unsigned long previousMillisMessage = 0;
unsigned long previousMillisLED = 0;
unsigned long previousMillisHum = 0;
const long intervalMessage = 3000;
const long intervalLED = 1000;
const long intervalHum = 1000;
// Function to connect to NTP server and set time
void NTPConnect() {
  // Set time using SNTP
  Serial.print("Setting time using SNTP");
  configTime(TIME_ZONE * 3600, 0, "pool.ntp.org", "time.nist.gov");
  time_t now = time(nullptr);
  while (now < 1510592825) { // January 13, 2018
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("done!");
}

// Callback function for message reception
void messageReceived(char *topic, byte *payload, unsigned int length) {
  Serial.print("Received [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// Function to connect to AWS IoT Core
void connectAWS() {
  delay(3000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println(String("Attempting to connect to SSID: ") + String(WIFI_SSID));

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  // Connect to NTP server to set time
  NTPConnect();

  // Set CA and client certificate for secure communication
  net.setTrustAnchors(&cert);
  net.setClientRSACert(&client_crt, &key);

  // Connect MQTT client to AWS IoT Core
  client.setServer(MQTT_HOST, 8883);
  client.setCallback(messageReceived);

  Serial.println("Connecting to AWS IoT");

  // Attempt to connect to AWS IoT Core
  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(1000);
  }

  // Check if connection is successful
  if (!client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to MQTT topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  Serial.println("AWS IoT Connected!");
}

// Function to publish message to AWS IoT Core
void publishMessage() {
  sensors_event_t event;
  float t = NAN, h = NAN;
  dht.temperature().getEvent(&event);

  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
     t = event.temperature;
  }

  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    h = event.relative_humidity;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  Temperature: ");
  Serial.print(t);
  Serial.println("°C");

  time_t currentTime = time(nullptr);

  // Create JSON document for message
  StaticJsonDocument<200> doc;
  doc["time"] = currentTime;
  doc["humidity"] = h;
  doc["temperature"] = t;

  // Serialize JSON document to string
  char jsonBuffer[200];
  serializeJson(doc, jsonBuffer);

  // Publish message to MQTT topic
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

bool checkTemperature() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    return false;
  }
  else {
     return (event.temperature > 21 && event.temperature < 24);
  }
}

bool checkHumidity() {
  sensors_event_t event;
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    return false;
  }
  else {
     return (event.relative_humidity > 30 && event.relative_humidity < 50);
  }
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  dht.begin();
  // Connect to AWS IoT Core
  connectAWS();
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillisMessage >= intervalMessage) {
    previousMillisMessage = currentMillis;
    publishMessage();
  }

  bool isTemperatureNormal = checkTemperature();
  
  if (isTemperatureNormal) {
    digitalWrite(ledpin1, HIGH);
  } else {
    if (currentMillis - previousMillisLED >= intervalLED) {
      previousMillisLED = currentMillis;
      digitalWrite(ledpin1, !digitalRead(ledpin1));
    }
  }

  bool isHumidityNormal = checkHumidity();
  
  if (isHumidityNormal) {
    digitalWrite(ledpin2, HIGH);
  } else {
    if (currentMillis - previousMillisHum >= intervalHum) {
      previousMillisHum = currentMillis;
      digitalWrite(ledpin2, !digitalRead(ledpin2));
    }
  }

  client.loop();
}
