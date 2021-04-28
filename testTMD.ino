
#include "TMD2635.h"
TMD2635 sensor1;
//TMD2635 sensor2;

const int SCLpin = 4;
const int SDApin = 5;

const int adr1 = 0x39;
//const int adr2 = 0x38;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(SDApin,SCLpin);
  sensor1.writedevadr(adr1);
  //sensor2.writedevadr(adr2);
  //sensor1._init_();
  //sensor2._init_(1);
 delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(sensor1.readregadr(0xAE),HEX);
  sensor1._init_();
  //Serial.println(sensor1.readregadr(0xAE),HEX);
  int first = sensor1.readProximity();
  //int second = sensor2.readProximity();
  Serial.println(first);
  //sensor1.NearProximity();
  //sensor1.writeregadr(0x80,0x05);
  //Serial.println(sensor1.readregadr(0x80),HEX);
  //Serial.println();
  //sensor1.writeregadr(0xA8,0x01);
  //Serial.println(sensor1.readregadr(0x80),HEX);
  //Serial.println();
  //Serial.println(sensor1.readregadr(0x8C),HEX);
  //Serial.println();
  //sensor1.Scan();
  Serial.println();
  delay(500);
}
