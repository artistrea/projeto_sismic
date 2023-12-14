#include <motor_pwm.h>
#include <fototransistors.h>
#include <msp430.h>

#define portAsButtonInput(x,y)                                      \
    P##x##DIR &= ~BIT##y;   /* Set Px.y as input */                 \
    P##x##REN |= BIT##y;    /* Enable Px.y internal resistance */   \
    P##x##OUT |= BIT##y;    /* Set Px.y as pull-Up resistance */    \
    P##x##IFG &= ~BIT##y   /* Px.y IFG cleared */


const int ccr0 = 255;

typedef int bool;

bool received_dt1, received_dt2;
uint16_t m1t1, m1t2, m2t1, m2t2, dt1, dt2;


void debounce();

void main() {
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    // // pra testar os pwm:
    // P1DIR |= 0x01;                  // configure P1.0 as output

    prepareMotorPWMs(ccr0);
    prepareFototransistors();

    setMotor1DutyCycle(30);
    setMotor2DutyCycle(30);

    __enable_interrupt();

    portAsButtonInput(1, 1);
    portAsButtonInput(2, 1);

    while (1) {
        if ((P1IFG & BIT1) || (P2IFG & BIT1)) {
            if (P1IFG & BIT1) {
                signed int duty_cycle = getMotor1DutyCycle();

                if (duty_cycle + 10 > 100) setMotor1DutyCycle(100);
                else setMotor1DutyCycle(duty_cycle + 10);

                debounce();
                P1IFG &= ~BIT1;                          // P1.1 IFG cleared after debounce
            } else {
                signed int duty_cycle = getMotor1DutyCycle();

                if (duty_cycle - 10 < 0) setMotor1DutyCycle(0);
                else setMotor1DutyCycle(duty_cycle - 10);

                debounce();
                P2IFG &= ~BIT1;                          // P2.1 IFG cleared after debounce
            }
        }

        if (received_dt1 && received_dt2) {
            if (dt1 > 0xf000) dt1 = 0xffff - dt1;
            if (dt2 > 0xf000) dt2 = 0xffff - dt2;
            int dif = dt2 - dt1;

            setMotor2DutyCycle(getMotor2DutyCycle() + 1);

            received_dt1 = 0;
            received_dt2 = 0;
        }
    }
}

void debounce() {
    volatile int i=16000;
    while (i--);
}


#pragma vector = TIMER1_A2_VECTOR
__interrupt void isr()
{
    switch(__even_in_range(TA1IV,4)) {
    case 2:
        m1t2 = m1t1;
        m1t1 = TA1CCR1;
        dt1 = m1t1 - m1t2;

        received_dt1 = 1;
        TA1CCTL1 &= ~CCIFG;
        break;
    case 4:
        m2t2 = m2t1;
        m2t1 = TA1CCR1;
        dt1 = m2t1 - m2t2;

        received_dt2 = 1;
        TA1CCTL2 &= ~CCIFG;
        break;
    default:
        break;
    }
}
