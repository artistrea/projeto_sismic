#ifndef MOTOR_PWM__H
#define MOTOR_PWM__H

#include <inttypes.h>

// accepts channel 0, 1 and 2
void prepareMotorPWMs(uint32_t ccr0);

// should be from 0 to 100
void setMotor1DutyCycle(int duty_cycle);

// should be from 0 to 100
void setMotor2DutyCycle(int duty_cycle);

uint32_t getMotor2DutyCycle();

#endif
