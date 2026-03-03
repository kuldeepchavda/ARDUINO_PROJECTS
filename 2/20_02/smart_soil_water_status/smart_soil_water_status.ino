#include <stdio.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
#define moisture A0
int buzz =  9;
DHT dht(3,DHT11);

void setup() {

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Hey!!");
Serial.begin(9600);
dht.begin();
}

void loop() {
int m = analogRead(moisture);
int h = dht.readHumidity();
int t = dht.readTemperature();
Serial.print(m);
Serial.print("|");
Serial.print(h);
Serial.print("|");
Serial.println(t);

if(m <500){
  lcd.clear();
  lcd.print("Soil watered!!");
  Serial.println("Soil watered!!");
  digitalWrite(buzz, LOW);
}else if (m>500 && m <=700){
  lcd.clear();
  lcd.print("Soil moderate watered!!");
  Serial.println("Soil moderate watered!!");
  digitalWrite(buzz, LOW);
}else{
  lcd.clear();
  lcd.print("dried out");
  Serial.println("Soil dried out!");
  digitalWrite(buzz, HIGH);
}
delay(5000);  
}
