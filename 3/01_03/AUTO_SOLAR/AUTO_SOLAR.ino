#include <Servo.h>

Servo myServo;

#define LDR_LEFT  2
#define LDR_RIGHT 3

int angle = 90;

void setup() {
  Serial.begin(9600);

  pinMode(LDR_LEFT, INPUT);
  pinMode(LDR_RIGHT, INPUT);

  myServo.attach(9);
  myServo.write(angle);

  Serial.println("Solar Tracker Started");
}

void loop() {

  int leftState  = digitalRead(LDR_LEFT);
  int rightState = digitalRead(LDR_RIGHT);

  Serial.print("Left: ");
  Serial.print(leftState);
  Serial.print(" | Right: ");
  Serial.print(rightState);
  Serial.print(" -> ");

  if (leftState == HIGH && rightState == LOW) {

    angle--;
    if (angle < 10) angle = 10;
    myServo.write(angle);

    Serial.print("Rotating LEFT | Angle: ");
    Serial.println(angle);
  }

  else if (rightState == HIGH && leftState == LOW) {

    angle++;
    if (angle > 170) angle = 170;
    myServo.write(angle);

    Serial.print("Rotating RIGHT | Angle: ");
    Serial.println(angle);
  }

  else if (leftState == HIGH && rightState == HIGH) {

    Serial.println("Centered on Light | Holding Position");
  }

  else {

    Serial.println("Low Light Detected | Idle Mode");
  }

  delay(4000);
}
