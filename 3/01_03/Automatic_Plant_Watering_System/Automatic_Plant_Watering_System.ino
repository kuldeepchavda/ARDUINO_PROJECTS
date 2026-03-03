int water; //random variable 
void setup() {
  pinMode(3,OUTPUT); //output pin for relay board, this will sent signal to the relay
  pinMode(6,INPUT); //input pin coming from soil sensor
  Serial.begin(9600);
}

void loop() { 
  water = analogRead(A0);
  Serial.println(water);

  
  if(water < 500)  {
    digitalWrite(3,HIGH); 
  }else{
    digitalWrite(3,LOW); 
  }
  delay(4000); 
}
