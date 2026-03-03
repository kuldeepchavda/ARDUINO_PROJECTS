#define TRIG 9
#define ECHO 10
#define BUZZER 6

long duration;
float distance;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
  Serial.begin(9600);
}

float getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);
  float dist = duration * 0.034 / 2;
  return dist;
}

void normalBeep() {
  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);
  delay(600);
}

void mediumBeep() {
  digitalWrite(BUZZER, HIGH);
  delay(150);
  digitalWrite(BUZZER, LOW);
  delay(200);
}

void panicBeep() {
  digitalWrite(BUZZER, HIGH);
  delay(80);
  
  digitalWrite(BUZZER, LOW);
  delay(80);
}

void loop() {

  distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 20 && distance <= 30) {
    normalBeep();
  }
  else if (distance > 10 && distance <= 20) {
    mediumBeep();
  }
  else if (distance > 0 && distance <= 10) {
    panicBeep();
  }
  else {
    digitalWrite(BUZZER, LOW);
    delay(2000);
  }
}
