#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int ldrPin = A0;
const float R_fixed = 10000.0;  // 10k resistor

void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  int adcValue = analogRead(ldrPin);
  
  float voltage = adcValue * (5.0 / 1023.0);

  float R_LDR = (5.0 - voltage) * R_fixed / voltage;

  float lux = 500.0 / (R_LDR / 1000.0);

  lcd.setCursor(0, 0);
  lcd.print("Light Intensity:");

  lcd.setCursor(0, 1);
  lcd.print(lux);
  lcd.print(" lux     ");

  delay(5000);
}
