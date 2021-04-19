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
  this->initialized = false;
  this->tmd2635Address = 0x39;
  this->i2cInterface = NULL;

  /* Initialize sensor parameters to defaults */
  this-> ...  */
}

bool TMD2635::begin(uint8_t tmd2635Address)
{
  return this->begin(Wire, tmd2635Address);
}

bool TMD2635::writeByte(uint8_t cmd, uint8_t val)
{
  this->i2cInterface->beginTransmission(this->tmd2635Address);
  this->i2cInterface->write(cmd);
  this->i2cInterface->write(val);
  if(0 != this->i2cInterface->endTransmission(true))
    return false;

  return true;
}

bool TMD2635::readWord(uint8_t cmd, uint16_t* val)
{
  *val = 0;
  
  this->i2cInterface->beginTransmission(this->tmd2635Address);
  this->i2cInterface->write(cmd);

  *val = this->i2cInterface->read();
  *val |= ((uint16_t)this->i2cInterface->read() << 8);
 
  return true;
}

int TMD2635::readProximity()
{
  uint16_t proximity = 0;
  bool readSuccess;
  
  readSuccess = this->readWord(0x80|0x20|0x18, &proximity);  // Read data register (0x80 = command, 0x20 = auto-increment)

  return proximity;
}

