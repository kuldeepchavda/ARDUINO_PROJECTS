#include <Servo.h>

Servo myServo;

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;

long duration;
float distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  myServo.attach(servoPin);
  myServo.write(0);    
  
  Serial.begin(9600);
}

void loop() {

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  duration = pulseIn(echoPin, HIGH);
 
  distance = duration * 0.034 / 2;

  Serial.println(distance);

  if (distance > 0 && distance < 10) {
    Serial.print("came close");
    myServo.write(90);   
    delay(800); 
    myServo.write(0);     
    delay(1500);    
    }
}
