#include <LiquidCrystal_I2C.h>

#define MOISTURE_PIN A0   // Analog pin for soil moisture sensor
#define THRESHOLD 600     // Adjust this after testing

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {

  int moistureValue = analogRead(MOISTURE_PIN);
  Serial.println(moistureValue);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture:");
  lcd.setCursor(0, 1);
  lcd.print(moistureValue);

  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);

  if (moistureValue > THRESHOLD) {
    lcd.print("Need Water!");
  } else {
    lcd.print("Soil OK");
  }

  delay(2000);
}
