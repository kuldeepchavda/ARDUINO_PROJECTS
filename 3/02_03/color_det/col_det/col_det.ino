#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// Most common I2C address is 0x27 or 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);


char colorCmd = 'N';


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("System Ready");
}


void loop() {
  if (Serial.available()) {
    colorCmd = Serial.read();    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Detected Color:");
    lcd.setCursor(0,1);

    if (colorCmd == 'R') lcd.print("RED");
    else if (colorCmd == 'G') lcd.print("GREEN");
    else if (colorCmd == 'B') lcd.print("BLUE");
    else lcd.print("NONE");
  }
}
