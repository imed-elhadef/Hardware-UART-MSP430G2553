/*
 * program.h
 *
 *  Created on: 3 janv. 2017
 *      Author: Imed Elhadef
 *      contact: imed.elhadef@arcangel.fr
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <msp430g2553.h>

#define BLINK_LED1()         (P1OUT ^= BIT0)// Toggle P1.0 using exclusive-OR
#define BLINK_LED2()         (P1OUT ^= BIT6)// Toggle P1.0 using exclusive-OR

#define DOOR_IS_LOW()        ((~P3IN) & BIT2)//Pull up
#define INPUT1_IS_LOW()      ((~P3IN) & BIT3)//Pull up

#define ACTIV_RELAY1()       (P2OUT |= BIT0)
#define DEACTIV_RELAY1()     (P2OUT &= ~BIT0)

#define ACTIV_RELAY2()       (P2OUT |= BIT1)
#define DEACTIV_RELAY2()     (P2OUT &= ~BIT1)

#define ACTIV_RELAY3()       (P2OUT |= BIT2)
#define DEACTIV_RELAY3()     (P2OUT &= ~BIT2)


#define LED1_ON()  (P1OUT |= BIT0)
#define LED1_OFF() (P1OUT &= ~BIT0)
#define LED2_ON()  (P1OUT |= BIT6)
#define LED2_OFF() (P1OUT &= ~BIT6)


void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);
void Hal_init (void);


#endif /* PROGRAM_H_ */
