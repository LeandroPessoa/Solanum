/*
 *  ==== DO NOT MODIFY THIS FILE - CHANGES WILL BE OVERWRITTEN ====
 *
 *  Generated from
 *      C:/ti/grace/grace_1_10_03_31_eng/packages/ti/mcu/msp430/csl/timer/ITimerx_A_init.xdt
 */

#include <msp430.h>

/**
 *  ======== Timer1_A3_init ========
 *  Initialize MSP430 Timer1_A3 timer
 */
void Timer1_A3_init(int periodo)
{
  CCTL0 = CCIE;                    // Habilita interrupção no registrador CCR0           
  TACTL = TASSEL_1 + MC_1 + ID_3;  //SMCLK/8 = 1MHz/8 = 125000hz      
  CCR0 =  periodo;             
}

void timerStart(void)
{
  TACTL |= MC_1;
  
}

void timerStop(void)
{
  
  TACTL &= TASSEL_1 + MC_0 + ID_3;
  
}