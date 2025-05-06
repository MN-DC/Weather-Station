// Course: Introduction to IoT
// Description: Temperature & Humidity Display
// Version: 1.0
// Author: Patrick Pham Luan & Micheal Nantel
// Dawson College - EET
// Date: 2025/05/06

#include <LiquidCrystal.h>  // Include the LiquidCrystal library for the LCD
#include <DHT.h>            //Include the DHT library for the Temperature & Humidity sensors


const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;  // Define the LCD pin connections: RS, Enable, Data4, Data5, Data6, Data7
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                    // Create an LCD object

#define DHTPIN 2       // DHT11 data pin connected to Pin 2
#define DHTTYPE DHT11  // Define sensor type


DHT dht(DHTPIN, DHTTYPE);  // Create a DHT sensor object

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);  // Initialize lcd display
  dht.begin();       // Initialize DHT11 sensor
}
void loop() {
  float temp = dht.readTemperature();  // read temp
  float hum = dht.readHumidity();      // read hum

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C | Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  lcd.clear();
  lcd.print("Temp:");
  lcd.print(temp);
  lcd.print(" C ");
  lcd.setCursor(0, 1);
  lcd.print(" Hum:");
  lcd.print(hum);
  lcd.print(" %");
  delay(1000);

  TemperatureControl(temp, hum);  // Call function to control RGB LED

  delay(1000);  // Wait 1 seconds before next reading
}
void TemperatureControl(float temperature, float humidity) {
  lcd.clear();
  if (temperature >= 18 && temperature <= 25 && humidity >= 40 && humidity <= 60) {
    Serial.println("Comfortable Environment.");
    lcd.print("Comfortable ");
    lcd.setCursor(0, 1);
    lcd.print("Environment.");
  } else if (temperature > 25 && humidity < 60) {
    Serial.println("Warm & Dry ");
    lcd.print("Warm & Dry ");
  } else if (temperature > 25 && humidity > 60) {
    Serial.println("Hot & Humid.");
    lcd.print("Hot & Humid.");
  } else if (temperature < 18 && humidity < 60) {
    Serial.println("Cold & Dry.");
    lcd.print("Cold & Dry.");
  } else if (temperature < 18 && humidity > 60) {
    Serial.println("Cold & Humid.");
    lcd.print("Cold & Humid.");
  } else if (humidity > 80 || isnan(temperature) || isnan(humidity)) {
    Serial.println("Extreme Humidity Detected or Sensor Error.");
    lcd.print("Sense Error.");
  }
}
