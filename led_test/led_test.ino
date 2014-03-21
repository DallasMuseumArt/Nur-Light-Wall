int lights[5] = { 2, 3, 4, 5, 6 };

void setup() { 
  Serial.begin(9600);
  
  for (int i = 0; i < 5; i = i + 1) {
    pinMode(lights[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 5; i = i + 1) {      
      analogWrite(lights[i], HIGH);
      Serial.println("light on");
      delay(500);
      //analogWrite(lights[i], LOW);
      //Serial.println("light off");
      //delay(500);
      
  }
    
}
