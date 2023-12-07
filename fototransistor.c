#include <motor_pwm.h>
#include <msp430.h>
#include <inttypes.h>

// prepares channels 0, 1 and 2 on TA0
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
