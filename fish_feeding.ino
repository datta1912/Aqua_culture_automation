#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASS "your_wifi_password"
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "your_username"
#define AIO_KEY "your_key"

WiFiClient wifi;
Adafruit_MQTT_Client mqtt(&wifi, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Define two Adafruit IO feeds for your motors
Adafruit_MQTT_Subscribe motor1Feed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/motor1");
Adafruit_MQTT_Subscribe motor2Feed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/motor2");
#define motor1A  5 // Connect to L293D pin 1
#define motor1B  4 // Connect to L293D pin 2
#define motor2A  2 // Connect to L293D pin 15
#define motor2B  16 // Connect to L293D pin 10

void motor1On() {
  // Code to turn on motor 1
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  Serial.println("Motor 1 turned on");
}

void motor1Off() {
  // Code to turn off motor 1
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  Serial.println("Motor 1 turned off");
}

void motor2On() {
  // Code to turn on motor 2
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  Serial.println("Motor 2 turned on");
}

void motor2Off() {
  // Code to turn off motor 2
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  Serial.println("Motor 2 turned off");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  mqtt.subscribe(&motor1Feed);
  mqtt.subscribe(&motor2Feed);
}

void loop() {
  // Ensure the client is connected to Adafruit IO
  if (!mqtt.connected()) {
    Serial.println("Reconnecting to Adafruit IO...");
    if (mqtt.connect()) {
      Serial.println("Connected to Adafruit IO");
      mqtt.subscribe(&motor1Feed);
      mqtt.subscribe(&motor2Feed);
    }
  }

  // Process messages from Adafruit IO
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &motor1Feed) {
      if (strcmp((const char*)motor1Feed.lastread, "ON") == 0) {
        motor1On();
      } else if (strcmp((const char*)motor1Feed.lastread, "OFF") == 0) {
        motor1Off();
      }
    } else if (subscription == &motor2Feed) {
      if (strcmp((const char*)motor2Feed.lastread, "ON") == 0) {
        motor2On();
      } else if (strcmp((const char*)motor2Feed.lastread, "OFF") == 0) {
        motor2Off();
      }
    }
  }
}





















#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <YourPHSensorLibrary.h> // Replace with the actual library for your pH sensor

// WiFi and Adafruit IO settings
#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASS "your_wifi_password"
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "your_username"
#define AIO_KEY "your_key"

WiFiClient wifi;
Adafruit_MQTT_Client mqtt(&wifi, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Define Adafruit IO feeds for your motors and pH value
Adafruit_MQTT_Subscribe motor1Feed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/motor1");
Adafruit_MQTT_Subscribe motor2Feed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/motor2");
Adafruit_MQTT_Publish pHFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/ph");

// Motor pins
#define motor1A 5
#define motor1B 4
#define motor2A 2
#define motor2B 16

// pH sensor pin
#define pH_SENSOR_PIN A0

void motor1On() {
  // Code to turn on motor 1
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  Serial.println("Motor 1 turned on");
}

void motor1Off() {
  // Code to turn off motor 1
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  Serial.println("Motor 1 turned off");
}

void motor2On() {
  // Code to turn on motor 2
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  Serial.println("Motor 2 turned on");
}

void motor2Off() {
  // Code to turn off motor 2
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  Serial.println("Motor 2 turned off");
}

// Initialize the pH sensor (replace with your sensor library)
YourPHSensorClass phSensor(pH_SENSOR_PIN);

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  mqtt.subscribe(&motor1Feed);
  mqtt.subscribe(&motor2Feed);
}

void loop() {
  if (!mqtt.connected()) {
    Serial.println("Reconnecting to Adafruit IO...");
    if (mqtt.connect()) {
      Serial.println("Connected to Adafruit IO");
      mqtt.subscribe(&motor1Feed);
      mqtt.subscribe(&motor2Feed);
    }
  }

  // Process messages from Adafruit IO (motor control)
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &motor1Feed) {
      if (strcmp((const char*)motor1Feed.lastread, "ON") == 0) {
        motor1On();
      } else if (strcmp((const char*)motor1Feed.lastread, "OFF") == 0) {
        motor1Off();
      }
    } else if (subscription == &motor2Feed) {
      if (strcmp((const char*)motor2Feed.lastread, "ON") == 0) {
        motor2On();
      } else if (strcmp((const char*)motor2Feed.lastread, "OFF") == 0) {
        motor2Off();
      }
    }
  }

  // Read pH value from the sensor (replace with your sensor library)
  float pHValue = phSensor.readpH();

  // Publish pH value to Adafruit IO
  if (mqtt.connected()) {
    pHFeed.publish(pHValue);
  }
}
