String Incoming_value;

void setup() 
{
  Serial.begin(9600);

  pinMode(7, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
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

    // LED 1
    if (Incoming_value == "ON1")
      digitalWrite(7, HIGH);
    else if (Incoming_value == "OFF1")
      digitalWrite(7, LOW);

    // LED 2
    else if (Incoming_value == "ON2")
      digitalWrite(3, HIGH);
    else if (Incoming_value == "OFF2")
      digitalWrite(3, LOW);

    // LED 3
    else if (Incoming_value == "ON3")
      digitalWrite(4, HIGH);
    else if (Incoming_value == "OFF3")
      digitalWrite(4, LOW);

    // LED 4
    else if (Incoming_value == "ON4")
      digitalWrite(5, HIGH);
    else if (Incoming_value == "OFF4")
      digitalWrite(5, LOW);

    // LED 5
    else if (Incoming_value == "ON5")
      digitalWrite(6, HIGH);
    else if (Incoming_value == "OFF5")
      digitalWrite(6, LOW);
  
  Serial.print("\n");
  }

//  delay(4000);  
}
