#include <Wire.h>
#include "Adafruit_VL6180X.h"
#include <Adafruit_APDS9500.h>
#include "TMD2635.h"

Adafruit_VL6180X vl = Adafruit_VL6180X();
Adafruit_APDS9500 apds;

TMD2635 sensor1;
//TMD2635 sensor2;

const int SCLpin = 4;
const int SDApin = 5;

const int adr1 = 0x39;
//const int adr2 = 0x38;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();


  ///////////////// VL //////////////////
  vl.begin();

  //////////////// APDS ////////////////
  // Try to initialize!
  apds.begin();
  /////////////// TMD //////////////
  //Wire.begin(SDApin,SCLpin);
  sensor1.writedevadr(adr1);
  //sensor2.writedevadr(adr2);
  
}

void loop() {
  //////////// VL //////////////
  uint8_t range = vl.readRange();
  Serial.print(range, BIN);Serial.print(" ");

  //////// TMD ///////////////
  sensor1._init_();
  int first = sensor1.readProximity();
  Serial.print(first, BIN); Serial.print(" ");

    //////////// APDS ///////////
  uint16_t gesture_flags = apds.getDetectedGestures();
  if(gesture_flags) {
    Serial.print("00000001");
  }
  else {
    Serial.print("00000000");
  }
  Serial.println();
  delay(100);
  
}
