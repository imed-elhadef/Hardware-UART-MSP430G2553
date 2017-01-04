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

#define BLINK_LED1()          (P1OUT ^= BIT0)// Toggle P1.0 using exclusive-OR
#define BLINK_LED2()          (P1OUT ^= BIT6)// Toggle P1.0 using exclusive-OR

#define LED1_ON()  (P1OUT |= BIT0)
#define LED1_OFF() (P1OUT &= ~BIT0)
#define LED2_ON()  (P1OUT |= BIT6)
#define LED2_OFF() (P1OUT &= ~BIT6)


void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);
void Hal_init (void);


#endif /* PROGRAM_H_ */
