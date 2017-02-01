/*
 * program.c
 *
 *  Created on: 3 janv. 2017
 *      Author: Imed Elhadef
 *      contact: imed.elhadef@arcangel.fr
 *      */
#include "program.h"

void Hal_init ()
{
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT

    P1OUT &= 0x00;               // Shut down everything
    P1DIR &= 0x00;

    P2OUT &= 0x00;               // Shut down everything
    P2DIR &= 0x00;

    P3OUT &= 0x00;               // Shut down everything
    P3DIR &= 0x00;


    P1DIR |= BIT0 + BIT6;            // Set P1.0 and P1.6 pins as output the rest are input
    P2DIR |= BIT0 + BIT1 + BIT2;     // Set P2.0, P2.1 and P2.2 as output the rest are input --> Relays output
    P3DIR |= BIT4 + BIT5 + BIT6;     // Set P3.4, P3.5 and P3.6 pins as output the rest are input 

    /*Init Interruption*/
    P1REN |= BIT3;                   // Enable internal pull-up/down resistors
    P1OUT |= BIT3;                   //Select pull-up mode for P1.3
    P1IE |= BIT3;                    // P1.3 interrupt enabled
    P1IES |= BIT3;                   // P1.3 Hi/lo edge
    P1IFG &= ~BIT3;                  // P1.3 IFG cleared

   /*Enable Timer A0 */
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode  
    CCR0 =  10000;                           // 12.5 Hz   


    /* Configure hardware UART */
    BCSCTL1 = CALBC1_1MHZ; // Set DCO to 1MHz
    DCOCTL = CALDCO_1MHZ; // Set DCO to 1MHz

    P1SEL = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2; // Use SMCLK
    UCA0BR0 = 104; // Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
    UCA0BR1 = 0; // Set baud rate to 9600 with 1MHz clock
    UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
    UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
    IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt

   __bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled

}

void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength)
{
 while(ArrayLength--){ // Loop until StringLength == 0 and post decrement
 while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
 UCA0TXBUF = *TxArray; //Write the character at the location specified py the pointer
 TxArray++; //Increment the TxString pointer to point to the next character
 }
}

