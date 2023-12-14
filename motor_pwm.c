#include <motor_pwm.h>
#include <msp430.h>
#include <inttypes.h>

#ifndef enableTimer(tx, ccr0)
#define enableTimer(tx, ccr0) T##tx##CTL = TASSEL__ACLK | ID__1 | MC__UP | TACLR; T##tx##CCR0=ccr0
#endif

#ifndef enablePinAsTimerOutput(px,py,txn,tchn, ccrn)
#define enablePinAsTimerOutput(px,py,txn,tchn, ccrn)        \
    P##px##DIR |= BIT##py;                                  \
    P##px##SEL |= BIT##py;                                  \
    T##txn##CCR##tchn = ccr0;                               \
    T##txn##CCTL##tchn = OUTMOD_7;                          \
    P##px##DS |= BIT##py
#endif

// prepares channels 0, 1 and 2 on TA0
void prepareMotorPWMs(uint32_t ccr0) {
    enablePinAsTimerOutput(1,2, A0, 1, 0);
    // Channel 2 Pin (1.3)
    enablePinAsTimerOutput(1,3, A0, 2, 0);

    enableTimer(A0, ccr0);
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
