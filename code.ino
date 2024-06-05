#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

#define soil_moisture_pin 34    // Soil moisture sensor pin
#define water_level_pin 35      // Water level sensor pin
#define mq7_pin 32              // MQ-7 sensor pin
#define motion_sensor_pin 18    // Motion sensor pin
#define ldr_pin 25              // LDR sensor pin

#define DHT_PIN 2               // DHT22 data pin
#define DHT_TYPE DHT22          // DHT type (DHT11, DHT22, DHT21)

#define buzzer_pin 4            // Buzzer pin

const char* ssid = "Three Bytes 5G";
const char* password = "4321@pasS";

// ThingSpeak settings
unsigned long myChannelNumber = 2556917;
const char * myWriteAPIKey = "8MSS1ZL7Y68GDQMY";

// WiFiClient instance
WiFiClient client;

// DHT sensor instance
DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");

  ThingSpeak.begin(client);  // Initialize ThingSpeak
  dht.begin();                // Initialize DHT sensor

  pinMode(buzzer_pin, OUTPUT); // Set buzzer pin as output
  pinMode(motion_sensor_pin, INPUT); // Set motion sensor pin as input

  // One-time beep sound on startup
  digitalWrite(buzzer_pin, HIGH); // Turn on buzzer
  delay(1000);                    // Wait for 1 second
  digitalWrite(buzzer_pin, LOW);  // Turn off buzzer
}

void loop() {
  int soilMoistureValue = analogRead(soil_moisture_pin);
  int waterLevelValue = analogRead(water_level_pin);
  int mq7Value = analogRead(mq7_pin);
  int motionValue = digitalRead(motion_sensor_pin);  // Read motion sensor value
  int ldrValue = analogRead(ldr_pin);               // Read LDR sensor value
  
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureValue);
  
  Serial.print("Water Level: ");
  Serial.println(waterLevelValue);

  Serial.print("MQ-7 Value: ");
  Serial.println(mq7Value);

  Serial.print("Motion Sensor: ");
  Serial.println(motionValue);

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Read temperature and humidity from DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Control buzzer based on water level
  if (waterLevelValue < 100) {
    digitalWrite(buzzer_pin, HIGH); // Turn on buzzer
  } else {
    digitalWrite(buzzer_pin, LOW);  // Turn off buzzer
  }

  // Send values to ThingSpeak
  ThingSpeak.setField(6, soilMoistureValue);
  ThingSpeak.setField(1, waterLevelValue);
  ThingSpeak.setField(5, temperature);
  ThingSpeak.setField(4, humidity);
  ThingSpeak.setField(2, mq7Value);
  ThingSpeak.setField(7, motionValue);  // Send motion sensor value as field 6
  ThingSpeak.setField(3, ldrValue);     // Send LDR sensor value as field 7
  int response = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(response == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(response));
  }
  
  delay(5000); // Delay 5 seconds between updates
}
