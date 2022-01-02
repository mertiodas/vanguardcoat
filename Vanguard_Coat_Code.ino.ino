/************
 * Author:Mert CENGIZ
 * Project Name:Vanguard Coat
 * Date:26/12/2021
 * Number:151220212100
 * Department:Electrical and Electronics Engineering
 */
#include <Adafruit_SSD1306.h>
#include "DHT.h"             // Library for DHT sensors
#define dhtPin 12            // data pin
#define dhtType DHT11        // DHT 11
#include <Wire.h>
#include<EEPROM.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#define OLED_RESET     -1 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define d_time 5000





DHT dht(dhtPin, dhtType);    // Initialise the DHT library

float humidityVal;           // humidity
float tempValC;              // temperature in degrees Celcius           
#define SSD1306_I2C_ADDRESS 0x3C


void setup() {
  Serial.begin(9600);  // to check the serial monitor
  display.display();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(2000);
  display.clearDisplay();
  dht.begin();               // start with reading the DHT sensor
  pinMode(7,OUTPUT);
  if(tempValC>20){
    digitalWrite(7,HIGH);
  }
}

void loop() {

  humidityVal = dht.readHumidity();        // get the humidity from the DHT sensor
  tempValC = dht.readTemperature();        // get the temperature in degrees Celcius from the DHT sensor

  // Check if all values are read correctly, if not try again and exit loop()
  if (isnan(humidityVal) || isnan(tempValC)) {
    Serial.println("Reading DHT sensor failed!");

    // end the loop() function
    return;
  }
  
  
  

  

  // Print all values to the serial monitor
  
  Serial.print("Humidity: ");
  Serial.print(humidityVal);
  Serial.print(" %\n");

  Serial.print("Temperature: ");
  Serial.print(tempValC);
  Serial.print(" °C\n ");
  
  
  
  /* to display in the oled */
    display.clearDisplay();
    display.setTextSize(1); // Draw 1X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 20);
    display.print(F("Temperature C:"));
    display.display();      // Show initial text
    display.println(tempValC);
    display.display();
    display.setTextSize(1); // Draw 1X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 40);
    display.print(F("Humidity:"));
    display.display();
    display.println(humidityVal);
    display.display();
    display.setTextSize(1); // Draw 1X-scale text
    display.setTextColor(WHITE);
    delay(d_time);
    
    
  /*display.setCursor(x,y);
   * display.println(text);
   * 
   */
  
}
