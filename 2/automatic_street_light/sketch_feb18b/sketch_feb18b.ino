const int ldrPin = A0;
const int ledPin = 9;
void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int lightValue = analogRead(ldrPin);
  Serial.println(lightValue);
  if (lightValue > 700) {    
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  delay(2000);
}