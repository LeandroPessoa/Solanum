/*
 *  ==== DO NOT MODIFY THIS FILE - CHANGES WILL BE OVERWRITTEN ====
 *
 *  Generated from
 *      C:/ti/grace/grace_1_10_03_31_eng/packages/ti/mcu/msp430/csl/communication/USCI_A0_init.xdt
 */

#include <msp430.h>

/*
 *  ======== USCI_A0_init ========
 *  Initialize Universal Serial Communication Interface A0 UART 2xx
 */
void USCI_A0_init(void)
{
    /* Disable USCI */
    UCA0CTL1 |= UCSWRST;

    /* 
     * Control Register 1
     * 
     * UCSSEL_2 -- SMCLK
     * ~UCRXEIE -- Erroneous characters rejected and UCAxRXIFG is not set
     * ~UCBRKIE -- Received break characters do not set UCAxRXIFG
     * ~UCDORM -- Not dormant. All received characters will set UCAxRXIFG
     * ~UCTXADDR -- Next frame transmitted is data
     * ~UCTXBRK -- Next frame transmitted is not a break
     * UCSWRST -- Enabled. USCI logic held in reset state
     * 
     * Note: ~<BIT> indicates that <BIT> has value zero
     */
    UCA0CTL1 = UCSSEL_2 + UCSWRST;
    
    /* 
     * Modulation Control Register
     * 
     * UCBRF_0 -- First stage 0
     * UCBRS_6 -- Second stage 6
     * ~UCOS16 -- Disabled
     * 
     * Note: ~UCOS16 indicates that UCOS16 has value zero
     */
    UCA0MCTL = UCBRF_0 + UCBRS_6;
    
    /* Baud rate control register 0 */
    UCA0BR0 = 130;
    
    /* Baud rate control register 1 */
    UCA0BR1 = 6;
    
    /* Enable USCI */
    UCA0CTL1 &= ~UCSWRST;
}
