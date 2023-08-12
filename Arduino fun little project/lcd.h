#ifndef LCD_H
#define LCD_H
#include <stdint.h>
#include <Arduino.h>
#define LCD_ADDR 0x3F
#define BACKLIGHT 0x08
#define EN 0x04

void initLCD();
void sendToLCD(uint8_t data, bool isChar = false);
void sendStringToLCD(const char *str);

#endif
