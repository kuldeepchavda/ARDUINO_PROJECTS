#include <PulseSensorPlayground.h>
#include <LiquidCrystal_I2C.h>

const int PulseWire = A0;
const int Threshold = 550;
const int buzzerPin = 8;

int alertBPM = 100;   




PulseSensorPlayground pulseSensor;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
  pulseSensor.begin();

  lcd.setCursor(0,0);
  // lcd.print("Heart Monitor");
  delay(2000);
  lcd.clear();
}

void loop() {
  int myBPM = pulseSensor.getBeatsPerMinute();

  if (pulseSensor.sawStartOfBeat()) {

    // Serial.print("BPM: ");
    Serial.println(myBPM);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Heart Rate:");

    lcd.setCursor(0,1);
    lcd.print(myBPM);
    // lcd.print(" BPM");

    if (myBPM > alertBPM) {
      digitalWrite(buzzerPin, HIGH);
    } else {
      digitalWrite(buzzerPin, LOW);
    }
  }

  delay(2000);
}
