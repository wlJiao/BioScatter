#include <msp430.h>
#include "sensor.h"

unsigned int Outburst_Value = 0;
unsigned int Outburst_Value_Shadow = 0;
static int Voltage_up_down_Flag = 0;

void SS_Init(void)
{
    /* Some pins */
    P1DIR &= ~BIT0;
    P3DIR &= ~BIT1;
    P5DIR &= ~BIT1;

    /* Set to three electrode mode */
    // SW_WRK Switch
    P4OUT |= BIT4;
    P4DIR |= BIT4;
    // SW_WE Switch
    P4OUT |= BIT5;
    P4DIR |= BIT5;
    // SHRT_RECE Switch
    P4OUT &= ~BIT6;
    P4DIR |= BIT6;

    /* Set the current amplification factor */
    Control_RFSwitch(1,1,1,1);
}


void Control_RFSwitch(int c_1,int c_2,int c_3,int c_4)
{
    if(c_1 == 1)
    {
        P4DIR |= BIT0;
        P4OUT |= BIT0;
    }
    else
    {
        P4DIR |= BIT0;
        P4OUT &= ~BIT0;
    }
    if(c_2 == 1)
    {
        P4DIR |= BIT1;
        P4OUT |= BIT1;
    }
    else
    {
        P4DIR |= BIT1;
        P4OUT &= ~BIT1;
    }
    if(c_3 == 1)
    {
        P1DIR |= BIT2;
        P1OUT |= BIT2;
    }
    else
    {
        P1DIR |= BIT2;
        P1OUT &= ~BIT2;
    }
    if(c_4 == 1)
    {
        P1DIR |= BIT3;
        P1OUT |= BIT3;
    }
    else
    {
        P1DIR |= BIT3;
        P1OUT &= ~BIT3;
    }
}

unsigned char exceptionFlag = 0;
void SSTask_Activate(void)
{
    /* Set some system flags for task switching */
    SS_stopFlag = 0;
    SS_exceptionFlag = 0;
    Voltage_up_down_Flag = 0;


    /* TB2 outputs PWM signals */
    // P5.0: Pin set to multiplexed output
    P5SEL1 &= ~BIT0;
    P5SEL0 |= BIT0;
    P5DIR |= BIT0;
    // Timer setting
    Outburst_Value = Outburst_Value_max;
    Outburst_Value_Shadow = Outburst_Value_max;
    TB2CCR0 = PWM_period;
    TB2CCR1 = Outburst_Value;
    TB2CTL = TBCLR + TBSSEL_1 + ID_0 + MC_1;
    TB2CCTL1 = CAP_0 + OUTMOD_6;

    /* TB0 adjusts the duty ratio of PWM signals output by TB2 */
    TB0CCR0 = 32768;
    TB0CTL = TBCLR + TBSSEL_1 + ID_0 + MC_1;
    TB0CCTL0 =  CCIE;

    /* Draws out the clock source ACLK to the communication circuit */
    P1SEL0 &= ~BIT1;
    P1SEL1 |= BIT1;

    /* Sensor circuit power supply */
    P4OUT &= ~BIT7;
}

void SSTask_SweepVolt(void)
{
    _DINT();

    TB0CCR0 = Update_Points;

    if(V_vp < 1.8)                 // When the voltage is less than 1.8V, the status is abnormal.
    {
        SS_exceptionFlag = 1;
        CM_SendData(0xF);
        goto SSTask_SweepVolt_STOP;
    }

    if(Voltage_up_down_Flag == 0)  // Voltage decline
    {
        if(Outburst_Value_Shadow > Outburst_Value_min)
        {
            Outburst_Value--;
            Outburst_Value_Shadow--;
        }
        else
        {
            Voltage_up_down_Flag = 1;
        }
    }
    else                           // Voltage increment

    {
        if(Outburst_Value_Shadow < Outburst_Value_max)
        {
            Outburst_Value++;
            Outburst_Value_Shadow++;
        }
        else
        {
            --Setup_senseCount;
            if(Setup_senseCount>0)
                TskSetReady(SSTASK_ACTIVATE);
            else
                SS_stopFlag=1;

SSTask_SweepVolt_STOP:
            Voltage_up_down_Flag = 0;
            Outburst_Value = 0;
            Outburst_Value_Shadow = 0;

            /* TB2 stop */
            P5SEL1 &= ~BIT0;
            P5SEL0 &= ~BIT0;
            P5OUT &= ~BIT0;
            P5DIR |= BIT0;
            TB2CTL = MC__STOP;
            TB2CCTL1 = 0;

            /* TB0 stop */
            TB0CTL = MC__STOP;
            TB0CCTL0 = 0;

            /* ACLK signal output pin reset to normal mode and output low level */
            P1SEL0 &= ~BIT1;
            P1SEL1 &= ~BIT1;
            P1OUT &= ~BIT1;
            P1DIR |= BIT1;

            /* Sensor power off */
            P4OUT |= BIT7;
        }
    }

    TB2CCR1 = Outburst_Value;

    TskExit();
    _EINT();
}

// Timer0_B0 interrupt service routine
#pragma vector = TIMER0_B0_VECTOR
__interrupt void TIMER0_B0_ISR(void)
{
    TskSetReady(SSTASK_SWEEPVOLT);
    __low_power_mode_off_on_exit();
}
