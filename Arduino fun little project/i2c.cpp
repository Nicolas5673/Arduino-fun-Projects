#include "i2c.h"
#include <Arduino.h>

void i2cStart() {
  digitalWrite(SDA_PIN, HIGH);
  digitalWrite(SCL_PIN, HIGH);
  digitalWrite(SDA_PIN, LOW);
  digitalWrite(SCL_PIN, LOW);
}

void i2cStop() {
  digitalWrite(SDA_PIN, LOW);
  digitalWrite(SCL_PIN, HIGH);
  digitalWrite(SDA_PIN, HIGH);
}

void i2cSendByte(uint8_t data) {
  for (int i = 0; i < 8; i++) {
    if (data & 0x80)
      digitalWrite(SDA_PIN, HIGH);
    else
      digitalWrite(SDA_PIN, LOW);
    data <<= 1;
    digitalWrite(SCL_PIN, HIGH);
    digitalWrite(SCL_PIN, LOW);
  }

  // Acknowledgment
  pinMode(SDA_PIN, INPUT);
  digitalWrite(SCL_PIN, HIGH);
  while (digitalRead(SDA_PIN));
  digitalWrite(SCL_PIN, LOW);
  pinMode(SDA_PIN, OUTPUT);
}
