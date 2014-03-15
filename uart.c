#include <msp430.h>


void uartInit()
{

  UCA0CTL1 |= UCSSEL_1;                     // CLK = ACLK
  UCA0BR0 = 0x03;                           // 32kHz/9600 = 3.41
  UCA0BR1 = 0x00;                           //
  UCA0MCTL = UCBRS1 + UCBRS0;               // Modulation UCBRSx = 3
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt


}

void sendData(unsigned char data)
{

UCA0TXBUF = data;
__delay_cycles(60000);
P1OUT ^= 1;

}

void sendDataNow(unsigned char data)
{

UCA0TXBUF = data;


}