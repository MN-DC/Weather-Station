// Course: Introduction to IoT
// Description: Temperature & Humidity Display
// Version: 1.0
// Author: Patrick Pham Luan & Micheal Nantel
// Dawson College - EET
// Date: 2025/05/06

#include <LiquidCrystal.h>  // Include the library to interface with an LCD display
#include <DHT.h>            // Include the library to use the DHT temperature and humidity sensor

// Define the pins on the Arduino connected to the LCD module
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;

// Initialize the LCD object with the above-defined pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define DHTPIN 2       // The DHT11 sensor data pin is connected to digital pin 2
#define DHTTYPE DHT11  // Define the type of sensor as DHT11

// Create an instance of the DHT object using the pin and sensor type
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);  // Start the serial monitor with a baud rate of 9600
  lcd.begin(16, 2);    // Set up the LCD’s number of columns and rows (16x2)
  dht.begin();         // Initialize the DHT sensor
}

void loop() {
  // Read temperature and humidity values from the sensor
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Print temperature and humidity values to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C | Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  // Display values on the LCD
  lcd.clear();          // Clear the LCD screen
  lcd.print("Temp:");   // Print "Temp:" on the first line
  lcd.print(temp);      // Print the temperature value
  lcd.print(" C ");     // Add units
  lcd.setCursor(0, 1);  // Move to the second line
  lcd.print(" Hum:");   // Print "Hum:" for humidity
  lcd.print(hum);       // Print the humidity value
  lcd.print(" %");      // Add units

  delay(1000);  // Wait 1 second

  TemperatureControl(temp, hum);  // Call a function to analyze and display comfort conditions

  delay(1000);  // Wait another second before looping again
}

// -------- Comfort Condition Functions --------

// Display message when temperature and humidity are comfortable
void Comfy() {
  Serial.println("Comfortable Environment.");
  lcd.print("Comfy Temp");
  lcd.setCursor(0, 1);
  lcd.print("Comfy Hum.");
}

// Display message when it is warm and dry
void Warm_Dry() {
  Serial.println("Warm & Dry ");
  lcd.print("Warm");
  lcd.setCursor(0, 1);
  lcd.print("Dry");
}

// Display message when it is warm and humidity is within a comfy range
void Warm_Comfy() {
  Serial.println("Warm & Comfy");
  lcd.print("Warm");
  lcd.setCursor(0, 1);
  lcd.print("Comfy");
}

// Display message when it is hot and humid
void Hot_Humid() {
  Serial.println("Hot & Humid.");
  lcd.print("Hot");
  lcd.setCursor(0, 1);
  lcd.print("Humid");
}

// Display message when it is cold and dry
void Cold_Dry() {
  Serial.println("Cold & Dry.");
  lcd.print("Cold.");
  lcd.setCursor(0, 1);
  lcd.print("Dry.");
}

// Display message when it is cold and humid
void Cold_Humid() {
  Serial.println("Cold & Humid.");
  lcd.print("Cold.");
  lcd.setCursor(0, 1);
  lcd.print("Humid");
}

// Display message when temperature is comfortable but air is too dry
void Comfy_dry() {
  Serial.println("Comfy but dry");
  lcd.print("Comfy Temp");
  lcd.setCursor(0, 1);
  lcd.print("Dry Humidity");
}

// Display message when temperature is comfortable but air is humid
void Comfy_Humid() {
  Serial.println("Comfy but Humid");
  lcd.print("Comfy Temp");
  lcd.setCursor(0, 1);
  lcd.print("Humid");
}

// Display error or extreme condition
void Error() {
  Serial.println("Extreme Humidity Detected or Sensor Error.");
  lcd.print("Sense Error.");
  lcd.setCursor(0, 1);
  lcd.print(" OR Extreme Humidity");
}

// Function to decide comfort message based on temperature and humidity levels
void TemperatureControl(float temperature, float humidity) {
  lcd.clear();  // Clear LCD before printing new condition

  // Check different ranges of temp and humidity, and call appropriate message function
  if (temperature >= 18 && temperature <= 25 && humidity >= 40 && humidity <= 60) {
    Comfy();
  } else if (temperature > 25 && humidity < 30) {
    Warm_Dry();
  } else if (temperature > 25 && humidity >= 30 && humidity <= 70) {
    Warm_Comfy();
  } else if (temperature > 25 && humidity > 70) {
    Hot_Humid();
  } else if (temperature < 18 && humidity < 30) {
    Cold_Dry();
  } else if (temperature < 18 && humidity > 70 && humidity < 80) {
    Cold_Humid();
  } else if (temperature >= 18 && temperature <= 25 && humidity < 40) {
    Comfy_dry();
  } else if (temperature >= 18 && temperature <= 25 && humidity > 60) {
    Comfy_Humid();
  } else if (humidity > 90 || isnan(temperature) || isnan(humidity)) {
    Error();
  }
}