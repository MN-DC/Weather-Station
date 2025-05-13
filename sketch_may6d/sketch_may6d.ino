// Course: Introduction to IoT
// Description: Temperature & Humidity Display
// Version: 1.0
// Author: Patrick Pham Luan & Micheal Nantel & Brandon Bucciero
// Dawson College - EET
// Date: 2025/05/13

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
  lcd.print(" ");       // Add units
  lcd.print((char)223); // Degree symbol
  lcd.print("C");       // Celsius
  lcd.setCursor(0, 1);  // Move to the second line
  lcd.print(" Hum:");   // Print "Hum:" for humidity
  lcd.print(hum);       // Print the humidity value
  lcd.print(" %");      // Add units

  delay(1000);  // Wait 1 second

  lcd.clear();                    // Clear the LCD screen
  temperatureControl(temp, hum);  // Call a function to analyze and display comfort conditions

  delay(1000);  // Wait another second before looping again
}

// ----------Checks Temperature---------
// Conditions look at temperature to identify whether it is hot, comfy or cold
void temperatureControl(float temperature, float humidity) {
  if (temperature > 25) {
    hot(humidity);
  } else if (temperature < 18) {
    cold(humidity);
  } else {
    comfy(humidity);
  }
}

// LCD controls for hot,
void hot(float humidity) {
  Serial.println("Hot");
  lcd.print("Hot.");
  humidityControl(humidity);
}
// cold,
void cold(float humidity) {
  Serial.println("Cold");
  lcd.print("Cold.");
  humidityControl(humidity);
}
// comfy.
void comfy(float humidity) {
  Serial.println("Comfy");
  lcd.print("Comfy.");
  humidityControl(humidity);
}

// Humidity Controls
void humidityControl(float humidity) {
  if (humidity > 60) {
    humid();
  } else if (humidity < 40) {
    dry();
  } else {
    moderate();
  }
}

// LCD controls for humid,
void humid() {
  Serial.print(" & humid.");
  lcd.setCursor(0, 1);
  lcd.print("Humid.");
}
// dry,
void dry() {
  Serial.print(" & dry.");
  lcd.setCursor(0, 1);
  lcd.print("Dry.");
}
// moderate.
void moderate() {
  Serial.print(" & moderate.");
  lcd.setCursor(0, 1);
  lcd.print("Moderate.");
}
