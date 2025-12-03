/*
********************************************************************************
@file         Deneyap_9EksenAtaletselOlcumBirimi.cpp
@mainpage     Deneyap 9 Dof IMU MMC5603NJ Arduino library source file
@version      v1.1.0
@date         Dec 03, 2025
@brief        Includes functions to control Deneyap 9 Dof IMU MMC5603NJ 
              Arduino library

Library includes:
--> Configuration functions
--> Data manipulation functions
--> I2C communication functions
********************************************************************************
*/

#include "Deneyap_9EksenAtaletselOlcumBirimi.h"
#include <Wire.h>

/**
  * @brief  I2C initialization
**/
bool MAGNETOMETER::begin(uint8_t address, TwoWire &wirePort) {
    _address = address >> 1; 
    
    Wire.begin();
    Wire.beginTransmission(_address);
    return (Wire.endTransmission() == 0);
}

/**
  * @brief  Reset and Set procedure (Degaussing)
**/
void MAGNETOMETER::RegRead() {
    writeRegister(Control_Reg_0, 0x20);
    delay(1);
    writeRegister(Control_Reg_0, 0x08);
    delay(1);
}

/**
  * @brief  Write specific register
**/
uint8_t MAGNETOMETER::writeRegister(uint8_t address, uint8_t value) {
    Wire.beginTransmission(_address);
    Wire.write(address);
    Wire.write(value);
    Wire.endTransmission();
    return 1;
}

/**
  * @brief  Read multiple registers
**/
uint8_t MAGNETOMETER::readRegisters(uint8_t address, uint8_t *data, size_t length) {
    Wire.beginTransmission(_address);
    Wire.write(address);
    if (Wire.endTransmission(false) != 0) return 0;
    if (Wire.requestFrom(_address, length) != length) return 0;
    for (size_t i = 0; i < length; i++) {
        *data++ = Wire.read();
    }
    return 1;
}

/**
  * @brief  Helper function to trigger measurement
**/
void MAGNETOMETER::triggerMeasurement() {
    writeRegister(0x1B, 0x01); 
    delay(10);
}

/**
  * @brief  Read X Axis
**/
int MAGNETOMETER::readMagnetometerX() {
    triggerMeasurement();

    byte data[9];
    if(readRegisters(0x00, (uint8_t *)data, 9) == 0) return 0;

    unsigned long rawValue = ((unsigned long)data[0] << 12) | ((unsigned long)data[1] << 4) | ((unsigned long)data[6] >> 4);
    
    float result = ((long)rawValue - 524288) * 0.00625;
    return (int)result;
}

/**
  * @brief  Read Y Axis
**/
int MAGNETOMETER::readMagnetometerY() {
    triggerMeasurement();

    byte data[9];
    if(readRegisters(0x00, (uint8_t *)data, 9) == 0) return 0;

    unsigned long rawValue = ((unsigned long)data[2] << 12) | ((unsigned long)data[3] << 4) | ((unsigned long)data[7] >> 4);
    
    float result = ((long)rawValue - 524288) * 0.00625;
    return (int)result;
}

/**
  * @brief  Read Z Axis
**/
int MAGNETOMETER::readMagnetometerZ() {
    triggerMeasurement();

    byte data[9];
    if(readRegisters(0x00, (uint8_t *)data, 9) == 0) return 0;

    unsigned long rawValue = ((unsigned long)data[4] << 12) | ((unsigned long)data[5] << 4) | ((unsigned long)data[8] >> 4);
    
    float result = ((long)rawValue - 524288) * 0.00625;
    return (int)result;
}

/**
  * @brief  Read All Data and Print
**/
int MAGNETOMETER::readData() {
    triggerMeasurement();
    byte data[9];
    if(readRegisters(0x00, (uint8_t *)data, 9) == 0) return 0;

    unsigned long rawX = ((unsigned long)data[0] << 12) | ((unsigned long)data[1] << 4) | ((unsigned long)data[6] >> 4);
    unsigned long rawY = ((unsigned long)data[2] << 12) | ((unsigned long)data[3] << 4) | ((unsigned long)data[7] >> 4);
    unsigned long rawZ = ((unsigned long)data[4] << 12) | ((unsigned long)data[5] << 4) | ((unsigned long)data[8] >> 4);

    float x = ((long)rawX - 524288) * 0.00625;
    float y = ((long)rawY - 524288) * 0.00625;
    float z = ((long)rawZ - 524288) * 0.00625;

    Serial.print("X ekseni = "); Serial.println(x);
    Serial.print("Y ekseni = "); Serial.println(y);
    Serial.print("Z ekseni = "); Serial.println(z);

    return 1;
}