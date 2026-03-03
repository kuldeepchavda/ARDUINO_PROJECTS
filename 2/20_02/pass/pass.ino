#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

const int touch1 = 2;
const int touch2 = 3;
const int buzzer = 8;

String input = "";
String password = "1010";

void setup() {
  pinMode(touch1, INPUT);
  pinMode(touch2, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  myServo.attach(9);
  myServo.write(0);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
}

void loop() {

  if (digitalRead(touch1) == HIGH) {
    Serial.println("1");
    input += "0";
    lcd.setCursor(0,1);
    lcd.print(input);
    delay(300);
  }

  if (digitalRead(touch2) == HIGH) {
    Serial.println("2");
    input += "1";
    lcd.setCursor(0,1);
    lcd.print(input);
    delay(300);
  }

  if (input.length() == 4) {
    if (input == password) {
      lcd.clear();
      lcd.print("Access Granted");
      myServo.write(90);
      delay(3000);
      lcd.clear();
      lcd.print("Thank you!!");
      myServo.write(0);
      delay(3000);
    } else {
      lcd.clear();
      lcd.print("Access Denied");
      tone(buzzer, 3000);
      delay(3000);
      noTone(buzzer);
    }

    input = "";
    lcd.clear();
    lcd.print("Enter Password:");
  }
}