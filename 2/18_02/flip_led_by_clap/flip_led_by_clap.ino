int soundPin = 2;
// int ledPin = 8;
int ledState = LOW;

void setup() {
  pinMode(soundPin, INPUT);
  Serial.begin(9600);
  // pinMode(ledPin, OUTPUT);
}

void loop() {
  int g = analogRead(A3);
  Serial.println(g);
  delay(3000);
  // if (digitalRead(soundPin) == HIGH) {
  //   if (ledState == LOW)
  //     ledState = HIGH;
  //   else
  //     ledState = LOW;

  //   // digitalWrite(ledPin, ledState);
  //   delay(500);   // wait so one clap counts once
  // }
}
