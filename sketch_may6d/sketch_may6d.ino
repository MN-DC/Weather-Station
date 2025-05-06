// Course: Introduction to IoT
// Description: Temperature Monitor with Sound Warning
// Version: 1.0
// Author: Patrick Pham Luan
// Dawson College - EET
// Date: 2025/02/02

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>  // Include the LCD library

// Defining Pins
#define bluePin 2
#define greenPin 3
#define redPin 4
#define tempPin 5
#define buzzerPin 9

// LCD Pins
#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2

// Create LCD object
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// === Hot Temperature Action Function ===
void hot() {
    digitalWrite(redPin, HIGH);  // Red LED on
    digitalWrite(greenPin, LOW); // Green LED off
    digitalWrite(bluePin, LOW);  // Blue LED off
    digitalWrite(buzzerPin, HIGH); // Buzzer on

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: High!");
    lcd.setCursor(0, 1);
    lcd.print("Warning!");
}

// === Normal Temperature Action Function ===
void normal() {
    digitalWrite(redPin, HIGH);   // Red LED on
    digitalWrite(greenPin, HIGH); // Green LED on
    digitalWrite(bluePin, LOW);   // Blue LED off
    digitalWrite(buzzerPin, LOW); // Buzzer off

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: Normal");
    lcd.setCursor(0, 1);
    lcd.print("All good!");
}

// === Cold Temperature Action Function ===
void cold() {
    digitalWrite(redPin, LOW);    // Red LED off
    digitalWrite(greenPin, LOW);  // Green LED off
    digitalWrite(bluePin, HIGH);  // Blue LED on
    digitalWrite(buzzerPin, LOW); // Buzzer off

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: Cold!");
    lcd.setCursor(0, 1);
    lcd.print("Check heating.");
}

// === Temperature Control Logic Function ===
void temperatureControl(float temp) {
    if (temp > 26) {
        hot();
    } else if (temp >= 25) {
        normal();
    } else {
        cold();
    }
}

OneWire oneWire(tempPin);       // Initialize OneWire protocol on pin tempPin.
DallasTemperature sensors(&oneWire); // DallasTemperature library simplifies

// === Setup routine runs once when you press reset ===
void setup() {
    // Defining the pin modes
    pinMode(bluePin, OUTPUT);  // Configure Blue pin of RGB
    pinMode(greenPin, OUTPUT); // Configure Green pin of RGB
    pinMode(redPin, OUTPUT);   // Configure Red pin of RGB
    pinMode(buzzerPin, OUTPUT); // Configure Buzzer pin
    pinMode(tempPin, INPUT);    // Configure Temperature Sensor pin

    // Startup Temperature Sensor
    sensors.begin();
    Serial.begin(9600);

    // Initialize LCD
    lcd.begin(16, 2);          // Set up the LCD's number of columns and rows
    lcd.print("Temp Monitor"); // Display startup message
    delay(2000);               // Show for 2 seconds
    lcd.clear();
}

// === The loop routine runs over and over again forever ===
void loop() {
    // Get temperature values
    float temp; // Defining local variables
    sensors.requestTemperatures();   // Request temperature from the sensor
    temp = sensors.getTempCByIndex(0); // Retrieve temperature in Celsius

    // Display the temperature on the Serial Monitor
    Serial.print("Temp: ");
    Serial.println(temp);

    // Call the temperature control function
    temperatureControl(temp);

    // Time delay of 1 second before taking the next reading
    delay(1000);
}