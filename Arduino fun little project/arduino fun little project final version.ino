#include "i2c.h"
#include "lcd.h"
#include "stepper.h"

String inputString = "";
bool stringComplete = false;


void setup() {
  pinMode(SDA_PIN, OUTPUT);
  pinMode(SCL_PIN, OUTPUT);
delay(1000); 
  Serial.begin(9600);  // Initialize serial communication

  // Initial message on Serial Monitor
  Serial.println("Send a string to display on the LCD:");

  i2cStart();
  i2cSendByte((LCD_ADDR << 1) | 0); 
  i2cStop();

  initLCD();
     moveAndDisplayStepperDirection(1);
  sendStringToLCD("Stepper Moved!");
  Serial.println("Stepper Moved");

}

void loop() {
  // Check if we received a full string from Serial Monitor
  if (stringComplete) {
    int steps = inputString.toInt(); // Convert string to integer steps
    moveAndDisplayStepperDirection(steps); // Move the stepper according to the input
    inputString = "";  // Clear the string
    stringComplete = false;  // Reset the flag
  }
}
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;

    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
