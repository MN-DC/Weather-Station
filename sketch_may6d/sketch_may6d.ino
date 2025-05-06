#include <LiquidCrystal.h>  // Include the LiquidCrystal library for the LCD
#include <DHT.h>

// Define the LCD pin connections: RS, Enable, Data4, Data5, Data6, Data7
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  // Create an LCD object
#define DHTPIN 2      // DHT11 data pin connected to Pin 2
#define DHTTYPE DHT11 // Define sensor type


DHT dht(DHTPIN, DHTTYPE); // Create a DHT sensor object
void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);    
    dht.begin();          // Initialize DHT11 sensor
}
void loop() {
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();
    lcd.clear();
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" °C | Humidity: ");
    Serial.print(hum);
    Serial.println(" %");

    lcd.print("Temp:");
    lcd.print(temp);
    lcd.print(" C ");
    lcd.setCursor(0, 1);  
    lcd.print(" Hum:");
    lcd.print(hum);
    lcd.print(" %");

    delay(500); // Wait 1 seconds before next reading
}