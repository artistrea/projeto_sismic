#include <motor_pwm.h>
#include <msp430.h>

#define portAsButtonInput(x,y)                                      \
    P##x##DIR &= ~BIT##y;   /* Set Px.y as input */                 \
    P##x##REN |= BIT##y;    /* Enable Px.y internal resistance */   \
    P##x##OUT |= BIT##y;    /* Set Px.y as pull-Up resistance */    \
    P##x##IFG &= ~BIT##y   /* Px.y IFG cleared */

#define portAsButtonInterrupt(x,y)                                     \
    P##x##DIR &= ~BIT##y;   /* Set Px.y as input */                 \
    P##x##REN |= BIT##y;    /* Enable Px.y internal resistance */   \
    P##x##OUT |= BIT##y;    /* Set Px.y as pull-Up resistance */    \
    P##x##IFG &= ~BIT##y;   /* Px.y IFG cleared */                   \
    P##x##IES |= BIT##y;    /* Px.y Hi/Lo edge */                   \
    P##x##IE  |= BIT##y     /* Px.y interrupt enabled */

const int ccr0 = 255;


void main() {
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    // // pra testar os pwm:
    // P1DIR |= 0x01;                  // configure P1.0 as output

    prepareMotorPWMs(ccr0);

    setMotor1DutyCycle(0);
    setMotor2DutyCycle(0);

    __enable_interrupt();

    portAsButtonInterrupt(1, 1);
    portAsButtonInterrupt(2, 1);

    while (1) {

    }
}


void debounce();

#pragma vector=PORT1_VECTOR
__interrupt void Port1(void) {
    signed int duty_cycle = getMotor1DutyCycle();

    if (duty_cycle + 10 > 100) setMotor1DutyCycle(100);
    else setMotor1DutyCycle(duty_cycle + 10);

    debounce();
    P1IFG &= ~BIT1;                          // P1.1 IFG cleared after debounce
}

#pragma vector=PORT2_VECTOR
__interrupt void Port2(void) {
    signed int duty_cycle = getMotor1DutyCycle();

    if (duty_cycle - 10 < 0) setMotor1DutyCycle(0);
    else setMotor1DutyCycle(duty_cycle - 10);

    debounce();
    P2IFG &= ~BIT1;                          // P2.1 IFG cleared after debounce
}

void debounce() {
    volatile int i=16000;
    while (i--);
}

