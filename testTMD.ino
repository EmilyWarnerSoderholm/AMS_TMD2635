

#include "TMD2635.h"
TMD2635 sensor1;
TMD2635 sensor2;

const int SCLpin = 4;
const int SDApin = 5;

const int adr1 = 0x39;
const int adr2 = 0x38;
int count = 0;
int all1 = 0; int avg1=0;
int all2 = 0; int avg2=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(SDApin,SCLpin);
  sensor1.writedevadr(adr1);
  sensor2.writedevadr(adr2);
  //sensor1.sensorRange();  
  //sensor2.sensorRange();
  //sensor1._init_();
  //sensor2._init_(1);
 delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(sensor1.readregadr(0xAE),HEX);
  sensor1._init_();
  sensor2._init_();
  //sensor1.Scan();
  //Serial.println(sensor1.readregadr(0xAE),HEX);
  int first = sensor1.readProximity();
  int second = sensor2.readProximity();
  //sensor1.sensorRange();  sensor2.sensorRange();
  //Serial.println(sensor1.sensorMin);Serial.println(sensor1.sensorMax);
  //Serial.println();
  //Serial.println(sensor2.sensorMin);Serial.println(sensor2.sensorMax);
  
  Serial.print("TP: "); Serial.print(first); 
  Serial.print("    BR: "); Serial.print(second); 
  Serial.print("    diff: "); Serial.print(first-second+2); Serial.println();
  //uint16_t difference = first-second;
  // Serial.print("difference: "); Serial.print(first-second); Serial.println();
  //Serial.println(second);
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
  //Serial.println("Done");

  delay(100);           // wait 5 seconds for next scan
}
