const int moisturePin = A0;
const int relayPin = 7;

int moistureValue = 0;
int threshold = 500;   // adjust after testing

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // relay OFF initially
}

void loop() {
  moistureValue = analogRead(moisturePin);
  Serial.println(moistureValue);

  if (moistureValue > threshold) {
    // soil dry -> pump ON
    digitalWrite(relayPin, LOW);
  } else {
    // soil wet -> pump OFF
    digitalWrite(relayPin, HIGH);
  }

  delay(1000);
}
