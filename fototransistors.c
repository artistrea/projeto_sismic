#include <fototransistors.h>
#include <msp430.h>
#include <inttypes.h>

void prepareFototransistors() {
    P2DIR &= ~BIT4; // as output
    P2SEL |= BIT4;  // P2.4 as TA2.1 peripheral

    P2DIR &= ~BIT5; // as output
    P2SEL |= BIT5;  // P2.5 as TA2.2 peripheral

    TA2CTL |= MC__CONTINOUS | TASSEL__SMCLK | TACLR;
    TA2CCTL1 |= CAP | CM_3 | CCIE | SCS;
    TA2CCTL2 |= CAP | CM_3 | CCIE | SCS;
}
