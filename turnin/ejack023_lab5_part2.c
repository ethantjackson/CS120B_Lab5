/*	Author: ejack023
 *	Lab Section: 023
 *	Assignment: Lab #5  Exercise #2
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo Link: https://www.youtube.com/watch?v=Uzx34V1sQM8&ab_channel=EthanJackson
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_STATES { SM_start, SM_wait, SM_init, SM_inc, SM_dec, SM_reset, SM_waitRelease} SM_STATE;
unsigned char input = 0x00;
void Tick_Fct() {
	input = ~PINA & 0x03;
	switch(SM_STATE) {
		case SM_start:
			SM_STATE = SM_init;
			break;
		case SM_init:
			SM_STATE =SM_wait;
		case SM_wait:
			if (input & 0x01 && input & 0x02) SM_STATE = SM_reset;
			else if (input & 0x01) SM_STATE = SM_inc;
			else if (input & 0x02) SM_STATE = SM_dec;
			else SM_STATE = SM_wait;
			break;
		case SM_inc:
			SM_STATE = SM_waitRelease;
			break;
		case SM_dec:
			SM_STATE = SM_waitRelease;
			break;
		case SM_reset:
			SM_STATE = SM_waitRelease;
			break;
		case SM_waitRelease:
			if (input & 0x01 && input & 0x02) SM_STATE = SM_reset;
			else if (!input) SM_STATE = SM_wait;
			else SM_STATE = SM_waitRelease;
			break;
		default: 
			SM_STATE = SM_wait;
			break;
	}	
	switch(SM_STATE) {
		case SM_start:
			break;
		case SM_init:
			PORTC = 7;
			break;
		case SM_wait:
			break;
		case SM_inc:
			if (PINC < 9)
			++PORTC;
			break;
 		case SM_dec:
			if (PINC > 0)
			--PORTC;
			break;
		case SM_reset:
			PORTC = 0;
		case SM_waitRelease:
			break;
		default:
			break;
	}
};

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	SM_STATE = SM_start;
	
    while (1) 
    {
		Tick_Fct();		
    }
}
