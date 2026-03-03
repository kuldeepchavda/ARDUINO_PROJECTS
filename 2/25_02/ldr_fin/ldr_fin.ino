#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int ldrPin = A0;
 
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Light Meter");
  delay(1500);
  lcd.clear();
}

void loop() {
  int adcValue = analogRead(ldrPin);
 
  float voltage = adcValue * (5.0 / 1023.0);
 
  if (voltage <= 0.01) voltage = 0.01;
 
  float lux = (2500 / voltage) - 500;

  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.print(" V | Approx Lux: ");
  Serial.println(lux);

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Lux:");

  lcd.setCursor(0, 1);
  lcd.print(lux);
  lcd.print("      ");  

  delay(2000);
}
