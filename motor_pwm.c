#include <motor_pwm.h>
#include <msp430.h>
#include <inttypes.h>

// prepares channels 0, 1 and 2 on TA0
void prepareMotorPWMs(uint32_t ccr0) {
    // Channel 1 Pin (1.2)
    P1DIR |= BIT2;                                  // Set timer CCR1 goto pin as output
    P1SEL |= BIT2;                                  // Set the pin as timer CCR1 output
    TA0CCR1 = 0;                                    // Modulate the PWM at 0%
    TA0CCTL1 = OUTMOD_7;
    
    // Channel 2 Pin (1.3)
    P1DIR |= BIT3;                                  // Set timer CCR1 goto pin as output
    P1SEL |= BIT3;                                  // Set the pin as timer CCR1 output
    TA0CCR2 = 0;                                    // Modulate the PWM at 0%
    TA0CCTL2 = OUTMOD_7;

    TA0CTL = TASSEL__ACLK | ID__1 | MC__UP | TACLR; // Set clock configuration and clear it
    TA0CCR0 = ccr0;                           // Set clock width
}

// should be from 0 to 100
void setMotor1DutyCycle(int duty_cycle) {
    TA0CCR1 = TA0CCR0*(duty_cycle/100);                                 // Modulate the PWM at duty_cycle%
}

// should be from 0 to 100
void setMotor2DutyCycle(int duty_cycle) {
    TA0CCR2 = TA0CCR0*(duty_cycle/100);                                 // Modulate the PWM at duty_cycle%
}

uint32_t getMotor1DutyCycle() {
    return TA0CCR1*100/TA0CCR0;                                 // Modulate the PWM at duty_cycle%
}

uint32_t getMotor2DutyCycle() {
    return TA0CCR2*100/TA0CCR0;                                 // Modulate the PWM at duty_cycle%
}
