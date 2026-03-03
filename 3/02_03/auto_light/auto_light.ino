#define LDR_PIN A0
#define PIR_PIN 2
#define LED_PIN 13

int ldrValue = 0;
int ldrThreshold = 500;   // Adjust after testing

bool ledState = false;
bool lastPirState = LOW;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
}
void loop() {

  ldrValue = analogRead(LDR_PIN);
  bool currentPirState = digitalRead(PIR_PIN);

  // Check brightness condition
  if (ldrValue > ldrThreshold) {   // Dark (change sign if needed)

    if (currentPirState == HIGH && lastPirState == LOW) {

      Serial.println("Human detected.");

      ledState = !ledState;

      if (ledState) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Dark environment -> Turning LED ON.");
      } else {
        digitalWrite(LED_PIN, LOW);
        Serial.println("Dark environment -> Turning LED OFF.");
      }

      Serial.println("-----------------------------");
    }

  } else {

    if (ledState == true) {
      Serial.println("Bright environment detected.");
      Serial.println("Forcing LED OFF.");
      Serial.println("-----------------------------");
    }

    digitalWrite(LED_PIN, LOW);
    ledState = false;
  }

  lastPirState = currentPirState;
}
