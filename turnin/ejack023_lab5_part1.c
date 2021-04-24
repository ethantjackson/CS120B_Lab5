/*	Author: ejack023
 *	Lab Section: 023
 *	Assignment: Lab #5  Exercise #1
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo Link: https://www.youtube.com/watch?v=POguTficzFI&ab_channel=EthanJackson
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    unsigned char input = 0x00;
    unsigned char output = 0x00;
    while (1) 
    {
	input = ~PINA & 0x0F;
	output = 0x00;
	if (input < 1);
	else if (input <= 2) output = 0x20;
	else if (input <= 4) output = 0x30;
	else if (input <= 6) output = 0x38;
	else if (input <= 9) output = 0x3C;
	else if (input <= 12) output = 0x3E;
	else output = 0x3F;
	if (input <= 4) output = output | 0x40;
	PORTC = output;
    }
}
