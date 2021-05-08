/*************************************************************************
Title:    Arduino TMD2635 Library
Authors:  Emily Soderholm <ewsoderholm@hotmail.com>
File:     $Id: $
License:  GNU General Public License v3

This is an Arduino-compatible TMD2635 proximity sensor library
LICENSE:
    Copyright (C) 2021 Emily Soderholm


I want the code to make a single reading from a sensor, and the main code should be able to input address ( so in the loop ask TMD1 to read a single value then TMD2 to read a single value, do some maths, print and repeat)

Below is code from another similar TMD sensor
*************************************************************************/

#include "TMD2635.h"

//TMD2635::TMD2635()
  // initialize variables here
    // send some dummy address, check that device returns NACK
    //SDA = SCL = 1;
    //SCL_IN = SDA_IN = 0;
       
//{}
void TMD2635::_init_()
{
    //for far proximity, uncomment the following the code:
    writeregadr(SOFT_RESET,0x01);
    writeregadr(PERS, 0x0F);
    writeregadr(CFG3, 0x84);

    
    //writeregadr(PROX_CFG0,0x47); //01000111
    //writeregadr(PROX_CFG1, 0x85); //10000101 ???
    //writeregadr(PWTIME, 0x11) ;
    //writeregadr(POFFSET_L, 0x93);
    writeregadr(PRATE, 0x22);
    writeregadr(PIHTL, 0xFC);
    writeregadr(PIHTH, 0x03);
    //writeregadr(PFILTER, 0x01);
    //PWLONG
    
    
    
    
    
    
    

    //if (mode==true)
    //{
    //NearProximity();
    //}
    //else
    //{
        //FarProximity()
    //}
    writeregadr(ENABLE,0x05); //
}

int TMD2635::sensorRange()
{
  
  while (millis() < 5000) {
    sensorValue = readProximity();

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }
}
int TMD2635::Scan()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");
  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    delay(5);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(1000);           // wait 5 seconds for next scan
}

uint16_t TMD2635::readProximity()
{
  uint8_t status=readregadr(STATUS);
  if (status>0)
  {
      writeregadr(ENABLE,0x05);
      writeregadr(CFG3, 0x84);// why here?
  }
  uint16_t Lreading=readregadr(PDATAL);
  uint16_t Hreading=readregadr(PDATAH); 
  //Hreading = Hreading & 0b00000011; 
  uint16_t DATA = 0;
  //Serial.println(Lreading,BIN);  Serial.println(Hreading, BIN);
  DATA=Hreading<<8; 
  DATA+=Lreading ;
  
  int proximity = map(DATA, sensorMax, sensorMin, distanceMin, distanceMax);
  return proximity;
} 


 uint16_t TMD2635::readregadr(uint8_t reg)
 {
     Wire.beginTransmission(ADDRESS);
     //delay(5);
     Wire.write(reg);
     delay(5);
     Wire.endTransmission();
     Wire.requestFrom(ADDRESS, 1); // We want one byte
     uint8_t val = Wire.read();
    return val;
 }
        
 void TMD2635::writeregadr(uint8_t reg, uint8_t val)
 {
   Wire.beginTransmission(ADDRESS);
   //delay(5);
   Wire.write(reg);
   //delay(5);
   Wire.write(val);
   //delay(5);
   Wire.endTransmission();
 
 }
 void TMD2635::NearProximity()
 {
     writeregadr(CFG6, 0x7F);  // CFG6
     writeregadr(PROX_CFG0, 0x45); // PROX_CFG0
     writeregadr(PROX_CFG1, 0x85); //PROX_CFG1
     
 }

 void TMD2635::writedevadr(uint8_t dev)
 {
   ADDRESS=dev;
 
 }
