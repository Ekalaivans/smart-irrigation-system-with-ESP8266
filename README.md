\\# smart-irrigation-system-with-ESP8266


#define BLYNK_TEMPLATE_ID "TMPL3J7LVt6_b"
#define BLYNK_TEMPLATE_NAME "MINI PROJECT 2"
#define BLYNK_AUTH_TOKEN "mYmcSSckcY-P393C5lF9YZUwNAFJGRCQ"
#define BLYNK_PRINT Serial
#include <DHT.h>        // Include the DHT library

#define DHTPIN D4       // Define the digital pin to which the DHT11 sensor is connected
#define DHTTYPE DHT11  // Define the type of DHT sensor (DHT11)
DHT dht(DHTPIN, DHTTYPE);  // Create a DHT object


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "KALAI";
char pass[] = "12341234";
double water ;

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode (D0,OUTPUT);
  pinMode (A0,INPUT);
   pinMode (D1,INPUT);
  digitalWrite(D0,HIGH);
dht.begin();         // Initialize the DHT sensor
  Blynk.begin(auth, ssid, pass);
  
}

void loop()
{
   water=0;
  water=analogRead(A0);
  water=water/10;
 water=102.40 - water ;
  Serial.println(water);
  Blynk.virtualWrite(V0,water);
 BLYNK_WRITE(V1);
}
 BLYNK_WRITE(V1)  {
    int pinValue = param.asInt();
    if (pinValue==1){
      digitalWrite(D0,LOW);
    }
    else if(pinValue==0)
    {
      digitalWrite(D0,HIGH);
    }
    
    delay(100);
Blynk.run();  // Run Blynk tasks

  delay(2000);  // Wait for 2 seconds between measurements

  // Read temperature and humidity from the DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the sensor data to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Send the sensor data to Blynk app
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, humidity);    
  
}
