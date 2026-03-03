#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16,2);
int signal= 10;
int led   = 7;
int state;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  lcd.init();
    lcd.setCursor(0, 0);
  lcd.backlight(); 
}

void loop() {
 int data  = digitalRead(signal);
 if(data == HIGH){
  if(state == LOW){
    lcd.clear();            
    lcd.setCursor(0, 0);  
    lcd.print("Motion-1");
    state = HIGH;
  } 
 }else if(data==LOW){
    if(state==HIGH){
      lcd.clear();         
      lcd.setCursor(0, 0);  
      lcd.print("Motion-0");
      state = LOW;
    }
  }
}
