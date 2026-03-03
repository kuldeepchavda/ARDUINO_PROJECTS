#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

#define SERVO_PIN 9
#define BUZZER_PIN 8

int userChoice = -1;
int compChoice = -1;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  myServo.attach(SERVO_PIN);
  pinMode(BUZZER_PIN, OUTPUT);

  randomSeed(analogRead(A0));

  lcd.setCursor(0,0);
  lcd.print("Select:");
  lcd.setCursor(0,1);
  lcd.print("1-STN 2-PPR 3-SCR");

  Serial.println("Game Started");
  Serial.println("Select: 1-STN 2-PPR 3-SCR");
}

void loop() {

  if (Serial.available()) {

    char input = Serial.read();

    if(input == '1') userChoice = 0;
    else if(input == '2') userChoice = 1;
    else if(input == '3') userChoice = 2;
    else return;

    Serial.print("User Selected: ");
    Serial.println(choiceName(userChoice));

    compChoice = random(0, 3);

    Serial.print("Computer Selected: ");
    Serial.println(choiceName(compChoice));

    moveServo(compChoice);

    showResult(userChoice, compChoice);

    delay(3000);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Select:");
    lcd.setCursor(0,1);
    lcd.print("1-STN 2-PPR 3-SCR");

    Serial.println("----------------------");
    Serial.println("Select: 1-STN 2-PPR 3-SCR");
  }
}

void moveServo(int choice) {

  if(choice == 0) myServo.write(0);
  if(choice == 1) myServo.write(90);
  if(choice == 2) myServo.write(180);

  delay(500);
}

void showResult(int user, int comp) {

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("U:");
  lcd.print(choiceName(user));

  lcd.setCursor(0,1);
  lcd.print("C:");
  lcd.print(choiceName(comp));

  delay(2000);

  lcd.clear();
  lcd.setCursor(0,0);

  if(user == comp) {
    lcd.print("Draw!");
    Serial.println("Result: Draw");
    drawTone();
  }
  else if((user == 0 && comp == 2) ||
          (user == 1 && comp == 0) ||
          (user == 2 && comp == 1)) {
    lcd.print("Winner: USER");
    Serial.println("Result: USER Wins");
    victoryTone();
  }
  else {
    lcd.print("Winner: COMP");
    Serial.println("Result: COMPUTER Wins");
    sadTone();
  }
}

String choiceName(int c) {
  if(c == 0) return "Stone";
  if(c == 1) return "Paper";
  if(c == 2) return "Scissor";
  return "";
}

// 🎉 Victory Sound
void victoryTone() {
  tone(BUZZER_PIN, 800, 200);
  delay(250);
  tone(BUZZER_PIN, 1200, 200);
  delay(250);
  tone(BUZZER_PIN, 1000, 200);
  delay(250);
  noTone(BUZZER_PIN);
}

// 😢 Sad Sound
void sadTone() {
  tone(BUZZER_PIN, 1000, 300);
  delay(350);
  tone(BUZZER_PIN, 600, 500);
  delay(550);
  noTone(BUZZER_PIN);
}

// 😐 Draw Sound
void drawTone() {
  tone(BUZZER_PIN, 900, 200);
  delay(250);
  noTone(BUZZER_PIN);
}
