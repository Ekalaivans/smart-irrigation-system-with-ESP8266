// Smart Irrigation System with ESP8266 + Blynk + DHT11

#define BLYNK_TEMPLATE_ID   "TMPL3J7LVt6_b"
#define BLYNK_TEMPLATE_NAME "MINI PROJECT 2"
#define BLYNK_AUTH_TOKEN    "mYmcSSckcY-P393C5lF9YZUwNAFJGRCQ"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// --- Pin Configuration ---
#define DHTPIN D4        // DHT11 data pin
#define DHTTYPE DHT11    // Sensor type
#define RELAY_PIN D0     // Relay or pump control
#define MOISTURE_PIN A0  // Soil moisture sensor (analog)
#define MANUAL_PIN D1    // Optional manual input switch

// --- Global Variables ---
DHT dht(DHTPIN, DHTTYPE);
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "KALAI";        // Your WiFi SSID
char pass[] = "12341234";     // Your WiFi Password

double waterLevel = 0;

// --- Setup ---
void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Pump OFF initially

  pinMode(MOISTURE_PIN, INPUT);
  pinMode(MANUAL_PIN, INPUT);

  dht.begin(); // Initialize DHT11

  Blynk.begin(auth, ssid, pass);

  Serial.println("Smart Irrigation System Started...");
}

// --- Main Loop ---
void loop() {
  Blynk.run();

  // Soil Moisture Reading
  int rawMoisture = analogRead(MOISTURE_PIN);
  waterLevel = (1024 - rawMoisture) / 10.0;  // Convert to percentage approx.
  Serial.print("Soil Moisture: ");
  Serial.println(waterLevel);
  Blynk.virtualWrite(V0, waterLevel);

  // Temperature & Humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (!isnan(temperature) && !isnan(humidity)) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    Blynk.virtualWrite(V2, temperature);
    Blynk.virtualWrite(V3, humidity);
  } else {
    Serial.println("Failed to read from DHT sensor!");
  }

  delay(2000); // Update every 2 seconds
}

// --- Blynk App Control (Relay On/Off) ---
BLYNK_WRITE(V1) {
  int pinValue = param.asInt();  // Read button value from Blynk app

  if (pinValue == 1) {
    digitalWrite(RELAY_PIN, LOW);   // Turn ON pump
    Serial.println("Pump ON (Manual)");
  } else {
    digitalWrite(RELAY_PIN, HIGH);  // Turn OFF pump
    Serial.println("Pump OFF (Manual)");
  }
}

