#include "lcd.h"
#include "i2c.h"

void sendToLCD(uint8_t data, bool isChar = false) {
  uint8_t upperNibble = data & 0xF0;
  uint8_t lowerNibble = (data << 4) & 0xF0;

  i2cStart();
  i2cSendByte((LCD_ADDR << 1) | 0); 
  i2cSendByte(upperNibble | BACKLIGHT | (isChar ? 0x01 : 0x00));
  i2cSendByte(upperNibble | BACKLIGHT | EN | (isChar ? 0x01 : 0x00));
  i2cSendByte(upperNibble | BACKLIGHT | (isChar ? 0x01 : 0x00));
  
  i2cSendByte(lowerNibble | BACKLIGHT | (isChar ? 0x01 : 0x00));
  i2cSendByte(lowerNibble | BACKLIGHT | EN | (isChar ? 0x01 : 0x00));
  i2cSendByte(lowerNibble | BACKLIGHT | (isChar ? 0x01 : 0x00));
  i2cStop();
}

void initLCD() {
  sendToLCD(0x33); 
  sendToLCD(0x32);
  sendToLCD(0x28); 
  sendToLCD(0x0C); 
  sendToLCD(0x06); 
  sendToLCD(0x01); 
  delay(5);
}

void sendStringToLCD(const char *str) {
  while (*str) {
    sendToLCD(*str, true);
    str++;
  }
}
