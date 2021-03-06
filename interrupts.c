/*
 *  ==== DO NOT MODIFY THIS FILE - CHANGES WILL BE OVERWRITTEN ====
 *
 *  Generated from
 *      C:/ti/grace/grace_1_10_03_31_eng/packages/ti/mcu/msp430/csl/system/System_init.xdt
 */

#include <msp430.h>

/*
 *  ======== System_init ========
 *  Initialize MSP430 Status Register
 */
void System_init(void)
{
    /* Clear oscillator fault flag with software delay */
    do
    {
        // Clear OSC fault flag
        IFG1 &= ~OFIFG;

        // 50us delay
        __delay_cycles(800);
    } while (IFG1 & OFIFG);


    /* 
     * IFG2, Interrupt Flag Register 2
     * 
     * UCB0TXIFG -- Interrupt pending
     * UCB0RXIFG -- Interrupt pending
     * ~UCA0TXIFG -- No interrupt pending
     * UCA0RXIFG -- Interrupt pending
     * 
     * Note: ~UCA0TXIFG indicates that UCA0TXIFG has value zero
     */
    IFG2 &= ~(UCB0TXIFG + UCB0RXIFG + UCA0RXIFG);

    /* 
     * IE2, Interrupt Enable Register 2
     * 
     * UCB0TXIE -- Interrupt enabled
     * UCB0RXIE -- Interrupt enabled
     * ~UCA0TXIE -- Interrupt disabled
     * UCA0RXIE -- Interrupt enabled
     * 
     * Note: ~UCA0TXIE indicates that UCA0TXIE has value zero
     */
    IE2 |= UCB0TXIE + UCB0RXIE + UCA0RXIE;

    /* 
     * SR, Status Register
     * 
     * ~SCG1 -- Disable System clock generator 1
     * ~SCG0 -- Disable System clock generator 0
     * ~OSCOFF -- Oscillator On
     * ~CPUOFF -- CPU On
     * GIE -- General interrupt enable
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    __bis_SR_register(GIE);

}
