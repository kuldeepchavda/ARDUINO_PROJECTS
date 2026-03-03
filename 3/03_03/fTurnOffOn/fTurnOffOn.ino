#define FAN_PIN 8
#define LIGHT_PIN 9

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);

  digitalWrite(FAN_PIN, LOW);
  digitalWrite(LIGHT_PIN, LOW);

  Serial.begin(9600);
}

void loop() {

  if (Serial.available()) {

    String c = Serial.readString();   // Read full string
    c.trim();                         // Remove \r \n and spaces

    Serial.print("Received: ");
    Serial.println(c);

    // FAN CONTROL
    if (c == "fan on") {
      digitalWrite(FAN_PIN, HIGH);
      Serial.println("Fan Turned ON");
    }
    else if (c == "fan of" || c == "fan off") {
      digitalWrite(FAN_PIN, LOW);
      Serial.println("Fan Turned OFF");
    }

    // LIGHT CONTROL
    else if (c == "light on") {
      digitalWrite(LIGHT_PIN, HIGH);
      Serial.println("Light Turned ON");
    }
    else if (c == "light of" || c == "light off") {
      digitalWrite(LIGHT_PIN, LOW);
      Serial.println("Light Turned OFF");
    }
    else {
      Serial.println("Invalid Command");
    }
  }
}
