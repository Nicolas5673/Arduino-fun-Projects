#include "stepper.h"
#include "i2c.h"
#include "lcd.h"

void controlA4988(bool enable, bool direction) {
  uint8_t controlPins = 0x00;
  if (enable) {
    controlPins |= 0b00000010; // Set the Enable pin (p1) to enable the driver
  }
  if (direction) {
    controlPins |= 0b00000001; // Set the Direction pin (p0) for desired direction
  }
  
  // Send the control pins to PCF8574
  i2cStart();
  i2cSendByte((STEPPER_ADDR << 1) | 0); // Send the address for write
  i2cSendByte(controlPins);
  i2cStop();
}
void moveAndDisplayStepperDirection(int steps) {
  bool direction = steps > 0; // Set direction
  String directionString = direction ? "Clockwise" : "Anti-Clockwise";

  controlA4988(true, direction); // Enable the stepper and set direction

  for (int i = 0; i < abs(steps); i++) {
    // Pulse the STEP pin
    i2cStart();
    i2cSendByte((STEPPER_ADDR << 1) | 0);
    i2cSendByte(0b00000010); // P1 controls STEP
    i2cStop();
    delay(2); 

    i2cStart();
    i2cSendByte((STEPPER_ADDR << 1) | 0);
    i2cSendByte(0x00);
    i2cStop();
    delay(2);
  }

  controlA4988(false, direction); // Disable the stepper

  sendStringToLCD("Stepper Moved ");
  sendStringToLCD(directionString.c_str());
  Serial.print("Stepper Moved ");
  Serial.println(directionString);
}
