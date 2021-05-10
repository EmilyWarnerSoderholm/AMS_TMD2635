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
  private:
    int ADDRESS =0x39; //default for first sensor
   
  public:
    uint16_t  readProximity();
    uint16_t readregadr(uint8_t reg);
    void writeregadr(uint8_t reg,uint8_t val);
    void NearProximity();
    void _init_();
    void writedevadr(uint8_t dev);
    int Scan();
    int sensorValue = 0;         // the sensor value
    int sensorMin = 800;        // minimum sensor value
    int sensorMax = 2000;
    int distanceMin = 0;        // minimum sensor value
    int distanceMax = 100;
    int sensorRange();
    float m = 857854; float n = -1.838;
    

    
    // register addresses
    enum regAddr
    {
    /////// Specified for near proximity (NP)! ////
    
    ENABLE       =   0x80, /**  ENABLE R/W Enables states and interrupts. Reset val 0x00 */

    ATIME        =   0x81, /**  ATIME R/W ADC integration time 0x00 */
    PTIME        =   0x82, /**  PRATE R/W Proximity time 0x1F */
    PRATE        =   PTIME,

    /** PROX related interrupt thresholds */
    PILTL        =   0x88, /**  PILTL R/W Proximity interrupt low threshold low byte 0x00 */
    PILTH        =   0x89, /**  PILTH R/W Proximity interrupt low threshold high byte 0x00 */
        // NP: IGNORE
    PIHTL        =   0x8A, /**  PIHTL R/W Proximity interrupt high threshold low byte 0x00 */
        // NP: contains the HIGH threshold (8-bit value)
    PIHTH        =   0x8B, /**  PIHTH R/W Proximity interrupt high threshold high byte 0x00 */
        // NP: IGNORE
        
    PERS         =   0x8C, /**  PERS R/W ALS and proximity interrupt persistence filters 0x00 */

    CFG0         =   0x8D, /**  CFG0 R/W Configuration zero 0x40 */
    PROX_CFG0    =   0x8E, /**  PCFG0 R/W Proximity configuration zero 0x4F */
        // NP: PGAIN (7:6) = 1 (00)
        // NP: PPULSE(5:0) = 5 (00101) PPULSE determines no of prox pulses to be transmitted
    PROX_CFG1    =   0x8F, /**  PCFG1 R/W Proximity configuration one 0x80 */
        // NP: PLDRIVE (3:0) = 7 (0111)
        // NP: PPULSE_LEN (3:0) = 12 (100)
    CFG1         =   0x90, /**  CFG1 R/W Configuration one 0x09 */
    REV_ID_1     =   0x91, /**  REVID R Revision ID 0x01 */
    ID           =   0x92, /**  ID R Device ID 0x10 */

    STATUS       =   0x9B, /**  STATUS R, SC Device status 0x00 */

    /** PROX related raw data counts PDATA= ADCval x 16/PPULSE, */
        // NP: APC is disabled, only the upper 8 bits are compared against the
        // threshold values contained in PILTL and PIHTL.
    PDATAL    =   0x9C, /**  PDATAL R Proximity ADC low data (8 bits) 0x00 */
    PDATAH     =   0x9D, /**  PDATAH R Proximity ADC high data (2 bits) 0x00 */
        //  NP: bits 1:0 contain the lower 2 bits of the 10-bit proximity value.
    //PDATA_START  =   DEVREG_PDATA_LOW,

    REV_ID_2     =   0xA6, /**  REVID2 R Revision ID two 0x05 */
    CFG2         =   0xA7, /**  CFG2 R/W Configuration two 0x00 */
    SOFT_RESET   =   0xA8, /**  SOFTRST R/W Soft reset 0x00 */
    PWTIME       =   0xA9, /**  SOFTRST R/W Soft reset 0x00 */
    CFG8         =   0xAA, /**  CFG8 R/W Configuration three 0x04 */
    CFG3         =   0xAB, /**  CFG3 R/W Configuration three 0x04 */
//    DEVREG_CFG4         =   0xAC, /**  CFG4 R/W Configuration four (must be set to 0x3D) 0x3F */
    CFG6         =   0xAE, /**  CFG6 R?W Configuration six 0x3F */
        // NP: APC = disabled by setting bit 6 = 1,
        // 0xAE = 0x7F

    PFILTER      =   0xB3, /**  PFILTER */

    POFFSET_L    =   0xC0, /**  POFFSETL R/W Proximity offset low data 0x00 */
    POFFSET_H    =   0xC1, /**  POFFSETH R/W Proximity offset high data 0x00 */

    /** Calibration relates registers */
    CALIB        =   0xD7, /**  CALIB R/W Proximity offset calibration 0x00 */
    CALIBCFG     =   0xD9, /**  CALIBCFG R/W Proximity offset calibration control 0x50 */
        //BINSRCH_TARGET(7:5) = 31 (011)
    CALIBSTAT    =   0xDC, /**  CALIBSTAT R Proximity offset calibration status 0x00 */
    INTENAB      =   0xDD, /**  INTENAB R/W Interrupt enables 0x00 */

    /** Factory data lot codes */
    FACT_CODE_L  =   0xE5, /**  FAC_L R Factory data low (lot code data) 0x00 to 0xFF */
    FACT_CODE_H  =   0xE6, /**  FAC_H R Factory data high (lot code data) 0x00 to 0xFF */
    TEST9        =   0x07, /** Must be set to this */

    };
     
};

#endif
