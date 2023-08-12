#ifndef I2C_H
#define I2C_H
#include <stdint.h>
#include <Arduino.h>
#define SDA_PIN 4
#define SCL_PIN 5

void i2cStart();
void i2cStop();
void i2cSendByte(uint8_t data);

#endif
