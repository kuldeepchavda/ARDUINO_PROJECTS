
int buzz = 7;
void setup() {  
  pinMode(8,OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  int val  = analogRead(A0);
  Serial.println(val);
  if(val > 55){
      digitalWrite(8,HIGH);
  }else{
      digitalWrite(8,LOW);
  }
  delay(2000); 
}
