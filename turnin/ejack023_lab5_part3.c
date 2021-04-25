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
enum SM_STATES { SM_start, SM_wait1, SM_pattern1, SM_waitRelease1, SM_wait2, SM_pattern2, SM_waitRelease2} SM_STATE;
unsigned char input = 0x00;
void Tick_Fct() {
	input = ~PINA & 0x03;
	switch(SM_STATE) {
		case SM_start:
			SM_STATE = SM_wait1;
			break;
		case SM_wait1:
			if (input & 0x01) SM_STATE = SM_pattern1;
			break;
		case SM_pattern1:
			SM_STATE = SM_waitRelease1;
			break;
		case SM_waitRelease1:
			if (!input) SM_STATE = SM_wait2;
			break;
		case SM_wait2:
			if (input & 0x01) SM_STATE = SM_pattern2;
			break;
		case SM_pattern2:
			SM_STATE = SM_waitRelease2;
			break;
		case SM_waitRelease2:
			if (!input) SM_STATE = SM_wait1;
			break;
		default: 
			SM_STATE = SM_wait1;
			break;
	}	
	switch(SM_STATE) {
		case SM_start:
			break;
		case SM_wait1:
			break;
		case SM_pattern1:
			PORTB = 0xAA;
			break;
		case SM_waitRelease1:
			break;
		case SM_wait2:
			break;
		case SM_pattern2:
			PORTB = 0x55;
			break;
		case SM_waitRelease2:
			break;
		default:
			break;
	}
};

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	SM_STATE = SM_start;
	
    while (1) 
    {
		Tick_Fct();		
    }
}
