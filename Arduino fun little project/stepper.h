#ifndef STEPPER_H
#define STEPPER_H

#define STEPPER_ADDR 0x20

void moveAndDisplayStepperDirection(int steps);
void controlA4988(bool enable, bool direction);

#endif
