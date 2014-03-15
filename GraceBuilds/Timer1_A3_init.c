/*
 *  ==== DO NOT MODIFY THIS FILE - CHANGES WILL BE OVERWRITTEN ====
 *
 *  Generated from
 *      C:/ti/grace/grace_1_10_03_31_eng/packages/ti/mcu/msp430/csl/timer/ITimerx_A_init.xdt
 */

#include <msp430.h>

/*
 *  ======== Timer1_A3_init ========
 *  Initialize MSP430 Timer1_A3 timer
 */
void Timer1_A3_init(void)
{
    /* TA1CCR0, Timer_A Capture/Compare Register 0 */
    TA1CCR0 = 4095;

    /* 
     * TA1CTL, Timer_A3 Control Register
     * 
     * TASSEL_1 -- ACLK
     * ID_3 -- Divider - /8
     * MC_1 -- Up Mode
     */
    TA1CTL = TASSEL_1 + ID_3 + MC_1 + TAIE;
}
