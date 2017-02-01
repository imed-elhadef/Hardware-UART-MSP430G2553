/*
 * main.c
 *
 *  Created on: 3 janv. 2017
 *      Author: Imed Elhadef
 *      contact: imed.elhadef@arcangel.fr
 *      */
/* Example code demonstrating the use of the hardware UART on the MSP430G2553 to receive and send data to PC terminal
 * After programming it is necessary to stop debugging and reset the uC before
 * connecting the terminal program to transmit and receive characters.
 * This demo will turn on the Red LED if an R is sent and turn it off if a r is sent.
 * Similarly G and g will turn on and off the green LED
 * It also transmits the received character back to the terminal.
 */
#include "program.h"


static volatile char data;

char door[] = "OPENED";
char receive[] = "Received command: ";
char unknown[] = "Config Packet Received";
char back[]= "\n\r";

void main(void)

{
    Hal_init();
    while(1)
    {
     while (DOOR_IS_LOW()) //The door is close
        {
           ACTIV_RELAY1();
           ACTIV_RELAY2();
           DACTIV_RELAY3();
        }

     //The door is open
     while (!DOOR_IS_LOW())
          {    
             ACTIV_RELAY3();
             DACTIV_RELAY1();
             DACTIV_RELAY2();
             //UARTSendArray(door, sizeof(door));
         
           }
     
    }
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{

data = UCA0RXBUF;
UARTSendArray(receive,sizeof(receive));
UARTSendArray(&data, 1);
UARTSendArray(back,sizeof(back));

switch(data){
 case 'R':
 {
    LED1_ON();
 }
 break;
 case 'r':
 {
   LED1_OFF();
 }
 break;
 case 'G':
 {
  LED2_ON();
 }
 break;
 case 'g':
 {
  LED2_OFF();
 }
 break;
 default:
 {
 UARTSendArray(unknown, sizeof(unknown));
 UARTSendArray(&data, 1);
 UARTSendArray(back,sizeof(back));
 }
 break;
 }
}


// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
   BLINK_LED2();                      // Toggle P1.6
   P1IFG &= ~BIT3;                     // P1.3 IFG cleared
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  BLINK_LED1();                             // Toggle P1.0
}



