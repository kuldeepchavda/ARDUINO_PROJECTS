#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define INC_BTN 2
#define DEC_BTN 3
#define START_BTN 4
#define BUZZER 8

int setTime = 0;       // Time in seconds
bool running = false;
unsigned long previousMillis = 0;

void setup() {
  pinMode(INC_BTN, INPUT);
  pinMode(DEC_BTN, INPUT);
  pinMode(START_BTN, INPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Adjust Timer");
}

void loop() {

  // Increase Time
  if(digitalRead(INC_BTN) == HIGH && !running){
    setTime += 10;  // Add 10 seconds
    delay(300);
  }

  // Decrease Time
  if(digitalRead(DEC_BTN) == HIGH && !running){
    if(setTime >= 10)
      setTime -= 10;
    delay(300);
  }

  // Start / Stop
  if(digitalRead(START_BTN) == HIGH){
    running = !running;
    delay(300);
  }

  // Countdown Logic
  if(running && setTime > 0){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= 1000){
      previousMillis = currentMillis;
      setTime--;
    }
  }

  // Display Time
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(setTime);
  lcd.print(" Sec   ");

  // When Time Ends
  if(setTime == 0 && running){
    digitalWrite(BUZZER, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TIME UP!");
    delay(3000);
    digitalWrite(BUZZER, LOW);
    running = false;
  }
}
