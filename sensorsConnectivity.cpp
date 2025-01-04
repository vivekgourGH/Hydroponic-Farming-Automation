#include <DHT.h>         // Include the DHT sensor library
#include <Wire.h>        // For I2C communication
#include <Adafruit_Sensor.h> // For advanced sensor functionalities

// Pin definitions
#define DHTPIN 2          // Pin connected to the DHT sensor
#define DHTTYPE DHT11     // Type of DHT sensor (DHT11, DHT22, etc.)
#define PH_SENSOR_PIN A0  // Pin connected to the pH sensor
#define TDS_SENSOR_PIN A1 // Pin connected to the TDS sensor
#define TEMP_SENSOR_PIN A2 // Example: Analog temperature sensor

// Create a DHT object
DHT dht(DHTPIN, DHTTYPE);

// Variables for sensor readings
float humidity = 0.0;
float temperature = 0.0;
float pHValue = 0.0;
float TDSValue = 0.0;
int rawAnalogValue = 0;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  dht.begin();        // Start the DHT sensor
  
  // Initialize sensors (if needed)
  pinMode(PH_SENSOR_PIN, INPUT);
  pinMode(TDS_SENSOR_PIN, INPUT);
  pinMode(TEMP_SENSOR_PIN, INPUT);

  Serial.println("Hydroponic Farming Automation System Initialized!");
}

void loop() {
  // Read DHT sensor
  humidity = dht.readHumidity();
  temperature = dht.readTemperature(); // Default is in Celsius
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");
  }

  // Read pH sensor
  rawAnalogValue = analogRead(PH_SENSOR_PIN);
  pHValue = (rawAnalogValue * 5.0 / 1023) * 3.5; // Example calibration
  Serial.print("pH Value: ");
  Serial.println(pHValue);

  // Read TDS sensor
  rawAnalogValue = analogRead(TDS_SENSOR_PIN);
  TDSValue = (rawAnalogValue * 5.0 / 1023) * 500; // Example TDS conversion
  Serial.print("TDS Value: ");
  Serial.println(TDSValue);

  // Read additional temperature sensor
  rawAnalogValue = analogRead(TEMP_SENSOR_PIN);
  float additionalTemp = (rawAnalogValue * 5.0 / 1023) * 100; // Example conversion
  Serial.print("Additional Temperature Sensor: ");
  Serial.println(additionalTemp);

  delay(2000); // Wait 2 seconds before the next reading
}
