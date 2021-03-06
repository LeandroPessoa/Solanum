/*
 *  ==== DO NOT MODIFY THIS FILE - CHANGES WILL BE OVERWRITTEN ====
 *
 *  Generated from
 *      C:/ti/grace/grace_1_10_03_31_eng/packages/ti/mcu/msp430/csl/communication/USCI_B0_init.xdt
 */

#include <msp430.h>

/*
 *  ======== USCI_B0_init ========
 *  Initialize Universal Serial Communication Interface B0 I2C 2xx
 */
void USCI_B0_init(void)
{
    /* Disable USCI */
    UCB0CTL1 |= UCSWRST;
    
    /* 
     * Control Register 0
     * 
     * ~UCA10 -- Own address is a 7-bit address
     * ~UCSLA10 -- Address slave with 7-bit address
     * ~UCMM -- Single master environment. There is no other master in the system. The address compare unit is disabled
     * UCMST -- Master mode
     * UCMODE_3 -- I2C Mode
     * UCSYNC -- Synchronous Mode
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;
    
    /* 
     * Control Register 1
     * 
     * UCSSEL_2 -- SMCLK
     * ~UCTR -- Receiver
     * ~UCTXNACK -- Acknowledge normally
     * ~UCTXSTP -- No STOP generated
     * ~UCTXSTT -- Do not generate START condition
     * UCSWRST -- Enabled. USCI logic held in reset state
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    UCB0CTL1 = UCSSEL_2 + UCSWRST;
    
    /* Enable USCI */
    UCB0CTL1 &= ~UCSWRST;
}
