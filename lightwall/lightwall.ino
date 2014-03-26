int sensors[5] = { A0, A1, A2, A3, A4 };
int lights[5] = { 2, 3, 4, 5, 6 };
int lightsActive[5] = { false, false, false, false, false };
int lastSensorReadings[5] = { 0, 0, 0, 0, 0 };

/**
 * Thresholds must be set on a per sensor basis. Each
 * Row represents the sensor thresholds for the arduinos
 * installed in the exhibition
 *
 * Arduino #1
 */
//int threshold[5] = { 460, 370, 370, 400, 410 };
 /*
 * Arduino #2
 */
//int threshold[5] = { 410, 520, 5000, 340, 500 };
 /*
 * Arduino #3
 */
//int threshold[5] = { 410, 400, 450, 410, 410 };
 /*
 * Arduino #4
//int threshold[5] = { 560, 410, 400, 410, 10000 };
 /*
 * Arduino #5
 */
//int threshold[5] = { 410, 520, 400, 400, 400 };


boolean isFirst = true;

#define FADESPEED 30
/**
 * Arduino #1 410
 */
#define THRESHOLD 410

#define ANALOGLOWTHRES 400
#define ANALOGHIGHTHRES 650
#define LIGHT 254

void setup() { 
  Serial.begin(9600);
  Serial.println("Initializing light wall");
  
  for (int i = 0; i < 5; i = i + 1) {
    pinMode(lights[i], OUTPUT);
  }
}

void loop() {
  if (isFirst) {
    Serial.println("Begin start up diagnostics");
    for (int i = 0; i < 5; i = i + 1) {  
      Serial.print("Initialize light #");
      Serial.println(i);    
      analogWrite(lights[i], LIGHT);
      delay(500);
      analogWrite(lights[i], LOW);
      delay(500);
      
    }
    
    isFirst = false;
  }
  
  for (int i = 0; i < 5; i = i + 1) {
    //int sensorReading = getSensorValue(sensors[i]);
    int sensorReading = analogRead(sensors[i]);
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(" Reading: ");
    Serial.println(sensorReading);
    
    if (sensorReading > threshold[i]) {
      //analogWrite(lights[i], sensorReading);

      Serial.print("TRIGGERED SENSOR ");
      Serial.print(i);
      Serial.print(" VALUE ");
      Serial.println(sensorReading);
      
      if (!lightsActive[i]) {
        // Turn on the light
        for (int a = 0; a < 20; a++) {
          //analogWrite(lights[i], LIGHT);
          int r = map(a, 0, 20, 0, LIGHT);
          analogWrite(lights[i], r);     
          delay(FADESPEED);
        }
        //analogWrite(lights[i], LIGHT);
        lightsActive[i] = true;
      }
    } else if (lastSensorReadings[i] > threshold[i]) {
      
      delay(250);
      
      /*
       * When the previous reading has dropped below the threshold
       * and the current reading is below the threshold fade the
       * light out to 0
       */
      for (int a = 20; a > -1; a--) {
        int r = map(a, 0, 20, 0, LIGHT);
        analogWrite(lights[i], r);
        
        delay(FADESPEED);
      }
      
      lightsActive[i] = false;
    }
    
    lastSensorReadings[i] = sensorReading;

  }
  
  Serial.println("");


}

// A more complex method to map digital values to analog values.  Use this
// if you want the brightness to dither based on distance

///**
// * Map an analog voltage reading (0 - 1023) to an analog write value (0 - 255)
// */
//int getSensorValue(int pin) {
//  int sensorValue = analogRead(pin);
//  sensorValue = constrain(sensorValue, 0, ANALOGHIGHTHRES);
//  return map(sensorValue, ANALOGLOWTHRES, ANALOGHIGHTHRES, 0, 255);
//}
