/*
 * motor_pwm.h
 *
 *  Created on: 7 de dez de 2023
 *      Author: artistreak
 */

#ifndef MOTOR_PWM_H_
#define MOTOR_PWM_H_


#include <inttypes.h>

// prepares TA0 channels 0, 1 and 2
// uses pins 1.2 and 1.3
void prepareMotorPWMs(uint32_t ccr0);

// should be from 0 to 100
void setMotor1DutyCycle(int duty_cycle);

// should be from 0 to 100
void setMotor2DutyCycle(int duty_cycle);

// returns 0 to 100
uint32_t getMotor1DutyCycle();

// returns 0 to 100
uint32_t getMotor2DutyCycle();


#endif /* MOTOR_PWM_H_ */
