#include <LiquidCrystal_I2C.h>

#define trigPin 9
#define echoPin 10
#define buzzer 6

LiquidCrystal_I2C lcd(0x27, 16, 2);

long duration;
float distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  Serial.begin(9600);
}

void loop() {

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Receive echo
  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.println(distance);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");

  lcd.setCursor(0, 1);
if (distance <= 20) {
    lcd.print("DANGER");
    tone(buzzer, 2000);
    delay(200);
    noTone(buzzer);
    delay(200);
  }
  
  else if (distance > 20 && distance < 40) {
    lcd.print("CAUTION");
    tone(buzzer, 1000);
    delay(400);
    noTone(buzzer);
    delay(400);
  }
  else if (distance >=40 && distance <400) {
    lcd.print("SAFE");
    noTone(buzzer);
  } else if (distance <5 ) {
    lcd.print("STOP !!");
    tone(buzzer, 2500);
  }
  
  else if(distance>400 ){
    lcd.print("Error recieving data");
    // tone(buzzer, 2000);
    delay(200);
    // noTone(buzzer);
    delay(200);
  }
 

  delay(1000);
}
