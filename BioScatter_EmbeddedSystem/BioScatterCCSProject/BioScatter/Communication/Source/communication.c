#include "communication.h"

void CM_Init(void)
{
    /* RX is enabled */
    P2OUT |= BIT3;
    P2DIR |= BIT3;

    /* TX is enabled */
    P6OUT &= ~BIT1;
    P6DIR |= BIT1;

    /* RX setting */
    // RX pull-down input
    P6SEL0 |= BIT0;
    P6SEL1 &= ~BIT0;
    P6REN |= BIT0;
    P6OUT &= ~BIT0;
    P6DIR &= ~BIT0;
    // Timer TB3 capture mode
    TB3CTL = TBCLR|TBSSEL__ACLK|MC__UP;
    TB3CCTL1 = CM__RISING|CAP__CAPTURE|CCIS__CCIA|CCIE ;
    TB3CCR1 = 0;
}


void CMTask_Activate(void)
{
    if(V_stopFlag == 1)
    {
        Setup_senseCount = SENSECOUNT;
        TskSetReady(VTASK_ACTIVATE);
    }
    TskExit();
}

void CM_SendData(unsigned char data)
{
    _DINT();

    unsigned char i, j, k;
    unsigned char saveSWOUT = P1OUT;
    unsigned char saveSWDIR = P1DIR;
    unsigned char saveSWSEL0 = P1SEL0;
    unsigned char saveSWSEL1 = P1SEL1;

    P1OUT |= BIT6;
    P1SEL0 &= ~BIT6;
    P1SEL1 &= ~BIT6;
    P1DIR |= BIT6;

    P6OUT &= ~BIT6;
    P6DIR |= BIT6;

    for(i=0; i<8; ++i)
    {
        if(((data>>i)&0x01) > 0)
            k = 12;
        else
            k = 6;

        for(j=0; j<k; ++j)
        {
            __no_operation();
            __no_operation();
            P6OUT ^= BIT6;
        }

        P6OUT &= ~BIT6;
        for(j=0; j<16-k; ++j)
        {
            __no_operation();
            __no_operation();
            __no_operation();
        }
    }

    P1OUT = saveSWOUT;
    P1SEL0 = saveSWSEL0;
    P1SEL1 = saveSWSEL1;
    P1DIR = saveSWDIR;

    _EINT();
}




// TIMER3_B1 interrupt service routine
#pragma vector = TIMER3_B1_VECTOR
__interrupt void TIMER3_B1_Interrupt(void)
{
    switch(__even_in_range(TB3IV, TBIV_14))
    {
    case TBIV__TBCCR1:
    {
        TskSetReady(CMTASK_ACTIVATE);
        __low_power_mode_off_on_exit();
    }
    }
}
