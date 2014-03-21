int sensors[5] = { A0, A1, A2, A3, A4 };
int lastSensorReadings[5] = { 0, 0, 0, 0, 0 };

#define THRESHOLD 10
#define ANALOGLOWTHRES 400
#define ANALOGHIGHTHRES 650

void setup() { 
  Serial.begin(9600);
}

void loop() {

  
  for (int i = 0; i < 5; i = i + 1) {
    Serial.print(" Sensor ");
    Serial.print(i);
    int sensorReading = getSensorValue(sensors[i]);

    Serial.print(" DVal: ");
    Serial.print(sensorReading);
    
    if (sensorReading > THRESHOLD) {
      Serial.print(" TRIGGERED ");
      Serial.println(i);
    }
  }
  
  Serial.println("");

}

/**
 * Map an analog voltage reading (0 - 1023) to an analog write value (0 - 255)
 */
int getSensorValue(int pin) {
  int sensorValue = analogRead(pin);
  return sensorValue;
  sensorValue = constrain(sensorValue, 0, ANALOGHIGHTHRES);
  Serial.print(" AVal: ");
  Serial.print(sensorValue);
  return map(sensorValue, ANALOGLOWTHRES, ANALOGHIGHTHRES, 0, 255);
}
