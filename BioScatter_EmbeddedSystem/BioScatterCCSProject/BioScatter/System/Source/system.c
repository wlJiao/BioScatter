#include "system.h"

/* System state */
volatile task_t curTask;
volatile uint16_t tskReady;
void (*tskList[TASK_COUNT])(void);
const uint8_t __lowest_bit_bitmap[] =
{
    /* 00 */ 0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 10 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 20 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 30 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 40 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 50 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 60 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 70 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 80 */ 7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* 90 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* A0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* B0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* C0 */ 6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* D0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* E0 */ 5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    /* F0 */ 4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};

static void SysListInit(void)  // Setting the tskList.
{
    int i;
    for(i=0; i<TASK_COUNT; ++i)
    {
        tskList[i] = null;
    }
    curTask = -1;
}

static void SysTickInit(void)  // Turn off the watchdog.
{
    WDTCTL = WDTHOLD | WDTPW ;
}

void SysSchedule(void)
{
    while(true)
    {
        curTask = __ffs(tskReady)-1;

        if(curTask>=0)
            tskList[curTask]();
        else
        {
            _EINT();
            __bis_SR_register(LPM3_bits);
        }
    }
}

void TskCreate(void (*entry)(void), task_t task)
{
    if(task < TASK_COUNT && task >= 0)
    {
        tskList[task] = entry;
    }
}

static void GPIO_Init()  // Setting the GPIO.
{
    P1DIR = 0xFF;
    P2DIR = 0xFF;
    P3DIR = 0xFF;
    P4DIR = 0xFF;
    P5DIR = 0xFF;
    P6DIR = 0xFF;

    P1OUT = 0x00;
    P2OUT = 0x00;
    P3OUT = 0x00;
    P4OUT = 0x00;
    P5OUT = 0x00;
    P6OUT = 0x00;

    PM5CTL0 &= ~LOCKLPM5;  // Disable the GPIO power-on default high-impedance mode
}


static void CS_Config(void)  // Set the system clock source to the external low-frequency crystal oscillator.
{
    XT_PORT_SEL1 |= XT_OUT_PIN;
    XT_PORT_SEL0 &= ~XT_OUT_PIN;
    XT_PORT_SEL1 |= XT_IN_PIN;
    XT_PORT_SEL0 &= ~XT_IN_PIN;

    CSCTL3 = SELREF__REFOCLK;
    CSCTL4 = SELA__REFOCLK | SELMS__REFOCLK;
    CSCTL5 = VLOAUTOOFF_1 | SMCLKOFF_1 | DIVM__1;
    CSCTL6 = XT1FAULTOFF_0 | DIVA__1 | XT1DRIVE_0 | XTS_0 | XT1AUTOOFF_0;

    do
    {
        CSCTL7 &= ~(XT1OFFG|DCOFFG);
        SFRIFG1 &= ~OFIFG;

    }while(SFRIFG1 & OFIFG);

    CSCTL3 = SELREF__XT1CLK;
    CSCTL4 = SELA__XT1CLK | SELMS__XT1CLK;
}

void SysInit(void)
{
    SysTickInit();

    CS_Config();
    GPIO_Init();

    SysListInit();
}


