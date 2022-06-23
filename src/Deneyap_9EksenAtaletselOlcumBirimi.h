/*
*****************************************************************************
@file         Deneyap_9EksenAtaletselOlcumBirimi.h
@mainpage     Deneyap 9 Dof IMU MMC5603NJ Arduino library header file
@version      v1.0.0
@date         June 23, 2022
@brief        This file contains all function prototypes and macros
              for Deneyap 9 Dof IMU MMC5603NJ Arduino library
*****************************************************************************
*/

#ifndef __MAGNETOMETER_H
#define __MAGNETOMETER_H

#include <Wire.h>
#include <Arduino.h>

#define Control_Reg_0 0x1B
#define Control_Reg_1 0x1D

class MAGNETOMETER {
public:
    bool begin(uint8_t address, TwoWire &wirePort = Wire);
    void RegRead();
    int readMagnetometerX();
    int readMagnetometerY();
    int readMagnetometerZ();
    int readData();

private:
    uint8_t _address;
    uint8_t writeRegister(uint8_t address, uint8_t value);
    uint8_t readRegisters(uint8_t address, uint8_t *data, size_t length);
};

#endif
