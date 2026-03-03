#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <DHT.h>

#define LDR_PIN A0
#define PIR_PIN 2
#define LED_PIN 13 
#define MQ2_PIN A1
#define DHT_PIN 3

#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial bt(10, 11); // RX, TX
DHT dht(DHT_PIN, DHTTYPE);

int ldrValue = 0;
int ldrThreshold = 500;

int gasValue = 0;
int gasThreshold = 80;

bool ledState = false;
bool lastPirState = LOW;
bool smokeAlertSent = false;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);
  bt.begin(9600);
  dht.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Smart Campus");
  lcd.setCursor(0,1);
  lcd.print("Initializing...");
  
  delay(5000);   // MQ-2 warmup
  lcd.clear();
}

void loop() {

  // ===== Sensor Readings =====
  ldrValue = analogRead(LDR_PIN);
  bool currentPirState = digitalRead(PIR_PIN);
  gasValue = analogRead(MQ2_PIN);
  
//  Serial.println("pir");
//  Serial.println(currentPirState);
//  Serial.println("ldr");
//  Serial.println(ldrValue);
//  Serial.println("gas");
//  Serial.println(gasValue);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  lcd.setCursor(0,0);

  // ===== Smoke Priority =====
  Serial.println("Smoke !");
  Serial.println(gasValue);Serial.println(gasThreshold);
  if (gasValue > gasThreshold) {

    lcd.print("!!! SMOKE !!! ");

    if (!smokeAlertSent) {
      Serial.println("Smoke Detected!");
      bt.println("ALERT: Smoke detected in campus area!");
      smokeAlertSent = true;
    }

  } else {

    smokeAlertSent = false;

    // ===== LDR + PIR =====
    if (ldrValue > ldrThreshold) {

      lcd.print("Dark ");
       Serial.println(lastPirState);
      if (currentPirState == HIGH && lastPirState == LOW) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
      }

      if (ledState)
        lcd.print("| LED ON ");
      else
        lcd.print("| LED OFF");

    } else {
      digitalWrite(LED_PIN, LOW);
      ledState = false;
      lcd.print("Bright Area   ");
    }
  }

  lastPirState = currentPirState;

  // ===== Temperature + Humidity Always Visible =====
  lcd.setCursor(0,1);

  if (isnan(temperature) || isnan(humidity)) {
    lcd.print("DHT Error      ");
  } else {
    lcd.print("T:");
    lcd.print(temperature);
    lcd.print("C H:");
    lcd.print(humidity);
    lcd.print("% ");
  }

  delay(3000);   // DHT11 needs slower reading
}
