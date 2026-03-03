#include <Servo.h>

Servo doorServo;

const int pirPin = 2;
const int servoPin = 9;

int doorOpenAngle = 90;   // Adjust if needed
int doorCloseAngle = 0;

bool doorOpen = false;

void setup() {
  pinMode(pirPin, INPUT);
  doorServo.attach(servoPin);
  doorServo.write(doorCloseAngle);
  Serial.begin(9600);
}

void loop() {

  int motion = digitalRead(pirPin);

  if (motion == HIGH && !doorOpen) {
    Serial.println("Opening Door");
    openDoorSlow();
    doorOpen = true;
    delay(5000);  // Keep door open for 5 seconds

     Serial.println("Closing Door");
    closeDoorSlow();
    doorOpen = false;
  }
}

void openDoorSlow() {
  for (int pos = doorCloseAngle; pos <= doorOpenAngle; pos++) {
    doorServo.write(pos);
    delay(30);   // Increase for slower movement
  }
}

void closeDoorSlow() {
  for (int pos = doorOpenAngle; pos >= doorCloseAngle; pos--) {
    doorServo.write(pos);
    delay(30);
  }
}
