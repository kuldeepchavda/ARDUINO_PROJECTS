#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int ledPins[4] = {2, 3, 4, 5};
int buzzer = 6;

int sequence[4];
int userInput[4];
int inputIndex = 0;

void setup() {

  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  randomSeed(analogRead(A0));

  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  pinMode(buzzer, OUTPUT);

  Serial.println("===== MEMORY GAME STARTED =====");

  lcd.setCursor(0, 0);
  lcd.print("MEMORY GAME");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(2000);

  generateSequence();
}

void loop() {

  if (Serial.available()) {

    char data = Serial.read();

    if (data == '\n' || data == '\r') return;

    Serial.print("Received: ");
    Serial.println(data);

    if (data >= '1' && data <= '4') {

      if (inputIndex < 4) {

        int value = data - '0';

        userInput[inputIndex] = value;
        inputIndex++;

        flashLED(value);

        lcd.setCursor(0, 1);
        lcd.print("Input:        ");   // clear line
        lcd.setCursor(7, 1);

        for (int i = 0; i < inputIndex; i++) {
          lcd.print(userInput[i]);
          lcd.print(" ");
        }
      }
    }

    if (data == '#') {

      Serial.println("Submit pressed (#)");

      if (inputIndex == 4) {
        checkSequence();
      } else {
        Serial.println("Not enough inputs!");
      }

      delay(3000);
      inputIndex = 0;
      generateSequence();
    }
  }
}

void generateSequence() {

  Serial.println("---- NEW RANDOM SEQUENCE ----");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("New Sequence");
  lcd.setCursor(0, 1);
  lcd.print("Watch...");

  delay(1500);

  for (int i = 0; i < 4; i++) {
    sequence[i] = random(1, 5);
  }

  Serial.print("Actual Sequence: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(sequence[i]);
    Serial.print(" ");
  }
  Serial.println();

  for (int i = 0; i < 4; i++) {
    flashLED(sequence[i]);
    delay(400);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your Turn");
  lcd.setCursor(0, 1);
  lcd.print("Enter 1-4");
  Serial.println("Waiting for user input...");
}

void flashLED(int number) {

  int index = number - 1;

  digitalWrite(ledPins[index], HIGH);
  tone(buzzer, 1000 + (index * 200));
  delay(400);
  digitalWrite(ledPins[index], LOW);
  noTone(buzzer);
}

void checkSequence() {

  Serial.print("User Input: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(userInput[i]);
    Serial.print(" ");
  }
  Serial.println();

  bool correct = true;

  for (int i = 0; i < 4; i++) {
    if (sequence[i] != userInput[i]) {
      correct = false;
      break;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RESULT:");

  if (correct) {

    Serial.println("RESULT: CORRECT ✅");
    lcd.setCursor(0, 1);
    lcd.print("YOU WIN!");

    tone(buzzer, 1800);
    delay(800);
    noTone(buzzer);

  } else {

    Serial.println("RESULT: WRONG ❌");
    lcd.setCursor(0, 1);
    lcd.print("YOU LOST!");

    tone(buzzer, 300);
    delay(2000);
    noTone(buzzer);
  }
}
