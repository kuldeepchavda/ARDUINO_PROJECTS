#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int irPin = 2;
int count = 0;

bool personDetected = false;

void setup() {
  pinMode(irPin, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("People Counter");
  delay(2000);
  lcd.clear();
}

void loop() {

  int sensorState = digitalRead(irPin);

  // IR gives LOW when object detected
  if (sensorState == LOW && personDetected == false) {
    count++;
    personDetected = true;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Visitors:");
    lcd.setCursor(0, 1);
    lcd.print(count);

    delay(300);   // debounce
  }

  // Reset when path is clear
  if (sensorState == HIGH) {
    personDetected = false;
  }
}
