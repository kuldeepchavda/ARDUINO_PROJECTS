#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

String Incoming_value;

void setup() 
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.println("Hey"); 

  pinMode(13, OUTPUT);
  pinMode(8, INPUT);
}

void loop()
{

  if(digitalRead(8) == HIGH){
    digitalWrite(13,HIGH); 
    }else{
      digitalWrite(13,LOW); 
      }
      
  if (Serial.available() > 0)
  {
    Incoming_value = Serial.readString();
    Incoming_value.trim();  
    Serial.println(Incoming_value);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Incoming msg:");
    lcd.setCursor(0,1);
    lcd.print(Incoming_value);
  }

//  delay(4000);  
}
