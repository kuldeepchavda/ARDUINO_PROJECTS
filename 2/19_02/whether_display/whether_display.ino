#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();
Serial.begin(9600);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print(h);
  Serial.print("|");
  Serial.println(t);
  lcd.clear();


  
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");

  lcd.setCursor(0,1);
  lcd.print("Hum: ");
  lcd.print(h);
  lcd.print(" %");

  delay(10000);
}
