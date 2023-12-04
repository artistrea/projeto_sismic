#include <msp430.h> 
#include <inttypes.h>
#include <motor_pwm.h>

// accepts channel 0, 1 and 2
void prepareMotorPWMs(uint32_t ccr0) {
    TA0CTL = TASSEL__ACLK | ID__1 | MC__UP | TACLR; // Set clock configuration and clear it
    TA0CCR0 = ccr0;                           // Set clock width

    TA0CCTL1 = OUTMOD_7;                            // Set output mode as set on ccr0, reset on ccr1

    // Channel 1 Pin (1.2)
    P1DIR |= BIT2;                                  // Set timer CCR1 goto pin as output
    P1SEL |= BIT2;                                  // Set the pin as timer CCR1 output
    TA0CCR1 = ccr0;                                 // Modulate the PWM at 100%
    
    // Channel 2 Pin (1.2)
    P1DIR |= BIT2;                                  // Set timer CCR1 goto pin as output
    P1SEL |= BIT2;                                  // Set the pin as timer CCR1 output
    TA0CCR1 = ccr0;                                 // Modulate the PWM at 100%
}

// should be from 0 to 100
void setMotor1DutyCycle(int duty_cycle) {
    TA0CCR1 = TA0CCR0*duty_cycle/100;                                 // Modulate the PWM at duty_cycle%
}

// should be from 0 to 100
void setMotor2DutyCycle(int duty_cycle) {
    TA0CCR1 = TA0CCR0*duty_cycle/100;                                 // Modulate the PWM at duty_cycle%
}

uint32_t getMotor2DutyCycle() {
    return TA0CCR1*100/TA0CCR0;                                 // Modulate the PWM at duty_cycle%
}
