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
//Instructs the conditions what to do
void Comfy() { 
  Serial.println("Comfortable Environment."); //prints in serial monitor 
  lcd.print("Comfy Temp"); //prints temperature feel on first row of LCD display
  lcd.setCursor(0, 1); //switches to second row of LCD display
  lcd.print("Comfy Hum."); //prints humidity feel on second row of display
}
void Warm_Dry(){
  Serial.println("Warm & Dry ");
    lcd.print("Warm");
    lcd.setCursor(0, 1);
    lcd.print("Dry");
}
void Warm_Comfy(){
  Serial.println("Warm & Comfy");
    lcd.print("Warm");
    lcd.setCursor(0, 1);
    lcd.print("Comfy");
}
void Hot_Humid(){
  Serial.println("Hot & Humid.");
    lcd.print("Hot");
    lcd.setCursor(0, 1);
    lcd.print("Humid");
}
void Cold_Dry(){
  Serial.println("Cold & Dry.");
    lcd.print("Cold.");
    lcd.setCursor(0, 1);
    lcd.print("Dry.");
}
void Cold_Humid(){
  Serial.println("Cold & Humid.");
    lcd.print("Cold.");
    lcd.setCursor(0, 1);
    lcd.print("Humid");
}
void Comfy_dry(){
  Serial.println("Comfy but dry");
    lcd.print("Comfy Temp");
    lcd.setCursor(0, 1);
    lcd.print("Dry Humidity");
}
void Comfy_Humid(){
  Serial.println("Comfy but Humid");
    lcd.print("Comfy Temp");
    lcd.setCursor(0, 1);
    lcd.print("Humid");
}
void Error(){ 
  Serial.println("Extreme Humidity Detected or Sensor Error.");
    lcd.print("Sense Error.");
    lcd.setCursor(0, 1);
    lcd.print(" OR Extreme Humidity");
}
void TemperatureControl(float temperature, float humidity) { //defines conditions depending on the levels of temperature & humidity
  lcd.clear(); 
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
  } else if (temperature < 18 && humidity > 70) {
    Cold_Humid();
  } else if (temperature >= 18 && temperature <= 25 && humidity < 40) {
    Comfy_dry();
  } else if (temperature >= 18 && temperature <= 25 && humidity > 60) {
    Comfy_Humid();
  } else if (humidity > 90 || isnan(temperature) || isnan(humidity)) {
    Error();
  }
}
