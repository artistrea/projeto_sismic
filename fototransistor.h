#ifndef FOTOTRANSISTOR__H
#define FOTOTRANSISTOR__H

#include <inttypes.h>
#include <msp430.h>

// sets up TA1.1 and 1.2 for capture
// uses ports 2.0 and 2.1
// interrupts on captures
void prepareFototransistors() {
    P2DIR &= ~BIT0; // as output
    P2SEL |= BIT0;  // P2.0 as TA1.1 peripheral

    P2DIR &= ~BIT1; // as output
    P2SEL |= BIT1;  // P2.1 as TA1.2 peripheral

    TA1CTL |= MC__CONTINOUS | TASSEL__SMCLK | TACLR;
    TA1CCTL1 |= CAP | CM_3 | CCIE | SCS;
    TA1CCTL2 |= CAP | CM_3 | CCIE | SCS;
}

#endif
