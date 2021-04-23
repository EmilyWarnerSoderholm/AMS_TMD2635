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

#include <TMD2635.h>

TMD2635::TMD2635()
{
  // initialize variables here
    // send some dummy address, check that device returns NACK
    SDA = SCL = 1;
    SCL_IN = SDA_IN = 0;
       
}
void _init_(bool mode)
{
    //for far proximity, uncomment the following the code:
    writeregadr(SOFTRST,0x01)
    writeregadr(PERS, 0x0F)
    writeregadr(CFG3, 0x84)
    //setregadr(CFG0, )
    //setregadr(CFG0, )
    if (mode==True)
    {
        NearProximity()
    }
    else
    {
        //FarProximity()
    }
    writeregadr(ENABLE,0x05) //
}
void i2c_dly(void)
{
}

void i2c_start(void)
{
  // i2c start bit sequence:
  SDA = 1; i2c_dly(); SCL = 1; i2c_dly(); SDA = 0; i2c_dly(); SCL = 0; i2c_dly();
}

void i2c_stop(void)
{
  // i2c stop bit sequence
  SDA = 0; i2c_dly(); SCL = 1; i2c_dly(); SDA = 1; i2c_dly();
}

unsigned char i2c_rx(char ack)
{
char x, d=0;
  SDA = 1; 
  for(x=0; x<8; x++) {
    d <<= 1;
    do {
      SCL = 1;
    }
    while(SCL_IN==0);    // wait for any SCL clock stretching
    i2c_dly();
    if(SDA_IN) d |= 1;
    SCL = 0;
  } 
  if(ack) SDA = 0;
  else SDA = 1;
  SCL = 1;
  i2c_dly();             // send (N)ACK bit
  SCL = 0;
  SDA = 1;
  return d;
}

bit i2c_tx(unsigned char d)
{
char x;
static bit b;
  for(x=8; x; x--) {
    if(d&0x80) SDA = 1;
    else SDA = 0;
    SCL = 1;
    d <<= 1;
    SCL = 0;
  }
  SDA = 1; SCL = 1; i2c_dly();
  b = SDA_IN;          // possible ACK bit
  SCL = 0;
  return b;
}




bool TMD2635::begin(uint8_t tmd2635Address)
{
  //SLEEP: PON=0, IDLE: PON=1, ACTIVE: PEN=1, 
  // 'Complete' PRATE, PROX_AVG: true will loop the last steps, false:
    // Update PDATA, SAI: true will go to IDLE, false: 
        //PWTIME (wait time) then loop over all ACTIVE stages)
    
    //return this->begin(Wire, tmd2635Address);
}

bool TMD2635::Write(uint8_t CHIP-ADDRESSWRITE, uint8_t REGISTER-ADDRESS, uint8_t DATA BYTEs )
{
  i2c_start();              // send start sequence
  i2c_tx(CHIP-ADDRESSWRITE);             // SRF08 I2C address with R/W bit clear
  i2c_tx(REGISTER-ADDRESS);             // SRF08 command register address
  i2c_tx(DATA BYTEs);             // command to start ranging in cm
  i2c_stop();               // send stop sequence
}

bool TMD2635::Read(uint8_t adr_clear, uint8_t adr_set, uint8_t reg, uint8_t cmd)
{
i2c_start();              // send start sequence
i2c_tx(adr_clear);             // SRF08 I2C address with R/W bit clear
i2c_tx(reg);             // SRF08 light sensor register address
i2c_start();              // send a restart sequence
i2c_tx(adr_set);             // SRF08 I2C address with R/W bit set
lightsensor = i2c_rx(1);  // get light sensor and send acknowledge. Internal register address will increment automatically.
rangehigh = i2c_rx(1);    // get the high byte of the range and send acknowledge.
rangelow = i2c_rx(0);     // get low byte of the range - note we don't acknowledge the last byte.
i2c_stop();               // send stop sequence
}


int TMD2635::readProximity()
{
  status=readregadr(STATUS);
  if (status>0)
  {
      writeregadr(ENABLE,0x05);
      writeregadr(CFG3, 0x84);
  }
  uint16_t Lreading=readregadr(PDATAL);
  uint16_t Hreading=readregadr(PDATAH); 
    
  uint16_t proximity = 0;
  proximity=Hreading<<8; 
  proximty+=Lreading;
  
  return proximity;
} 


 void readregadr(unit8_t reg)
 {
     Wire.beginTransmission(ADDRESS);
     Wire.write(reg);
     Wire.endTransmission();
     Wire.requestFrom(ADDRESS, 1); // We want one byte
     uint8_t val = Wire.read();
    return val;
 }
        
 void TMD2635::writeregadr(unit8_t reg, uint8_t val)
 {
   Wire.beginTransmission();
   Wire.write(reg);
   Wire.write(val);
   Wire.endTransmission();
 
 }
 void TMD2635::writedevadr(unit8_t dev)
 {
   ADDRESS=dev
 
 }
 void TMD2635::NearProximity()
 {
     setadr(CFG6, 0x7F)  // CFG6
     setard(PROX_CFG0, 0,45) // PROX_CFG0
     setadr(PROX_CFG1, 0x85) //PROX_CFG1
     
 }
 /** Wire.beginTransmission(0x39);
    Wire.write(REGISTER_ADDRESS);
    Wire.write(0x18);
    Wire.endTransmission();
    
    Wire.beginTransmission(CHIP_ADDRESS);
    Wire.write(REGISTER_ADDRESS);
    Wire.endTransmission();
    Wire.requestFrom(CHIP_ADDRESS, 1); // We want one byte
    uint8_t val = Wire.read();
    
    
    Wire.beginTransmission(deviceAddress);    // get the sensors attention 
    Wire.write(registerAddress);    // move your memory pointer to registerAddress
    Wire.endTransmission();           // completes the ‘move memory pointer’ transaction
    Wire.requestFrom(deviceAddress, 2); // send me the data from 2 registers
    firstRegisterByte = Wire.read();             // byte from registerAddress
    */
}

