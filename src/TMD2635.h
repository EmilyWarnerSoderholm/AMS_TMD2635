/*************************************************************************
Title:    Arduino TMD2635  Library Header
Authors:  Emily Soderholm <ewsoderholm@hotmail.com>
File:     $Id: $
License:  GNU General Public License v3

This is an Arduino-compatible TMD2635 proximity sensor library 
LICENSE:
    Copyright (C) 2021 Emily Soderholm

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.


    file defines all addresses and functions in .cpp file and variables used.

*************************************************************************/

#ifndef _TMD2635_H_
#define _TMD2635_H_

#include <Wire.h>
#include <Arduino.h>


class TMD2635
{
  public:
    TMD2635();
    bool begin(uint8_t tmd2635Address = 0x39);
    bool begin(TwoWire& i2cInterface, uint8_t tmd2635Address = 0x39);
    int readProximity();
    bool proximityReady();

    // register addresses
    enum regAddr
    {
{
    DEVREG_ENABLE       =   0x80, /**  ENABLE R/W Enables states and interrupts. Reset val 0x00 */

    DEVREG_ATIME        =   0x81, /**  ATIME R/W ADC integration time 0x00 */
    DEVREG_PTIME        =   0x82, /**  PRATE R/W Proximity time 0x1F */
    DEVREG_PRATE        =   DEVREG_PTIME,

    /** PROX related interrupt thresholds */
    DEVREG_PILTL        =   0x88, /**  PILTL R/W Proximity interrupt low threshold low byte 0x00 */
    DEVREG_PILTH        =   0x89, /**  PILTH R/W Proximity interrupt low threshold high byte 0x00 */
    DEVREG_PIHTL        =   0x8A, /**  PIHTL R/W Proximity interrupt high threshold low byte 0x00 */
    DEVREG_PIHTH        =   0x8B, /**  PIHTH R/W Proximity interrupt high threshold high byte 0x00 */
 
    DEVREG_PERS         =   0x8C, /**  PERS R/W ALS and proximity interrupt persistence filters 0x00 */

    DEVREG_CFG0         =   0x8D, /**  CFG0 R/W Configuration zero 0x40 */
    DEVREG_PROX_CFG0    =   0x8E, /**  PCFG0 R/W Proximity configuration zero 0x4F */
    DEVREG_PROX_CFG1    =   0x8F, /**  PCFG1 R/W Proximity configuration one 0x80 */
    DEVREG_CFG1         =   0x90, /**  CFG1 R/W Configuration one 0x09 */
    DEVREG_REV_ID_1     =   0x91, /**  REVID R Revision ID 0x01 */
    DEVREG_ID           =   0x92, /**  ID R Device ID 0x10 */

    DEVREG_STATUS       =   0x9B, /**  STATUS R, SC Device status 0x00 */

    /** PROX related raw data counts */
    DEVREG_PDATA_LOW    =   0x9C, /**  PDATAL R Proximity ADC low data 0x00 */
    DEVREG_PDATA_HI     =   0x9D, /**  PDATAH R Proximity ADC high data 0x00 */
    DEVREG_PDATA_START  =   DEVREG_PDATA_LOW,

    DEVREG_REV_ID_2     =   0xA6, /**  REVID2 R Revision ID two 0x05 */
    DEVREG_CFG2         =   0xA7, /**  CFG2 R/W Configuration two 0x00 */
    DEVREG_SOFT_RESET   =   0xA8, /**  SOFTRST R/W Soft reset 0x00 */
    DEVREG_PWTIME       =   0xA9, /**  SOFTRST R/W Soft reset 0x00 */
    DEVREG_CFG8         =   0xAA, /**  CFG8 R/W Configuration three 0x04 */
    DEVREG_CFG3         =   0xAB, /**  CFG3 R/W Configuration three 0x04 */
//    DEVREG_CFG4         =   0xAC, /**  CFG4 R/W Configuration four (must be set to 0x3D) 0x3F */
    DEVREG_CFG6         =   0xAE, /**  CFG6 R?W Configuration six 0x3F */

    DEVREG_PFILTER      =   0xB3, /**  PFILTER */

    DEVREG_POFFSET_L    =   0xC0, /**  POFFSETL R/W Proximity offset low data 0x00 */
    DEVREG_POFFSET_H    =   0xC1, /**  POFFSETH R/W Proximity offset high data 0x00 */

    /** Calibration relates registers */
    DEVREG_CALIB        =   0xD7, /**  CALIB R/W Proximity offset calibration 0x00 */
    DEVREG_CALIBCFG     =   0xD9, /**  CALIBCFG R/W Proximity offset calibration control 0x50 */
    DEVREG_CALIBSTAT    =   0xDC, /**  CALIBSTAT R Proximity offset calibration status 0x00 */
    DEVREG_INTENAB      =   0xDD, /**  INTENAB R/W Interrupt enables 0x00 */

    /** Factory data lot codes */
    DEVREG_FACT_CODE_L  =   0xE5, /**  FAC_L R Factory data low (lot code data) 0x00 to 0xFF */
    DEVREG_FACT_CODE_H  =   0xE6, /**  FAC_H R Factory data high (lot code data) 0x00 to 0xFF */

    };
  private:
    TwoWire* i2cInterface;
    bool initialized;
    uint8_t tmd2635Address;
    bool writeByte(uint8_t cmd, uint8_t val);
    bool readWord(uint8_t cmd, uint16_t* val);
     
};

#endif

