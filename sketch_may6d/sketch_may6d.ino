// Course: Introduction to IoT
// Description: Temperature & Humidity Monitor 
// Version: 1.0
// Author: Patrick Pham Luan & Micheal Nantel
// Dawson College - EET
// Date: 2025/02/02

#include <OneWire.h> 
#include <DHT.h> // Incude Temperature & Humidity
#include <LiquidCrystal.h>  // Include the LCD library

// Defining Pins
#define DHTPIN 2 //The pin the temp sensor is connected to
#define DHTTYPE DHT11 //Defining the sensot type for librbary
#define

// LCD Pins
const int rs = 7, en = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;

// Create LCD object
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);


OneWire oneWire(tempPin);       // Initialize OneWire protocol on pin tempPin.
DallasTemperature sensors(&oneWire); // DallasTemperature library simplifies

// === Setup routine runs once when you press reset ===
void setup() {
    //Set pin 2 as Input
    pinMode(DHTPIN, INPUT);
    // Startup Temperature Sensor
    sensors.begin();
    Serial.begin(9600);

    // Initialize LCD
    lcd.begin(16, 2);          // Set up the LCD's number of columns and rows
    lcd.print("Temp & Humidity Monitor"); // Display startup message
    delay(2000);               // Show for 2 seconds
    lcd.clear();
}

// === The loop routine runs over and over again forever ===
void loop() {
    // Get temperature values
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();


    // Display the temperature on the Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temp);

    // Call the temperature control function
    temperatureControl(temp);

    // Time delay of 1 second before taking the next reading
    delay(1000);
}