/*	Author: mrayy002
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum State{Wait,Start,Start1,Unlock,Lock,} state =Wait;

void tick() {
	switch(state) {
		case Wait: {
			if((PINA &0x04) ==0x04) {
				state =Start;
			}
			else if((PINA &0x80) ==0x80) {
				state =Lock;
			}
			else {
				state =Wait;
			}
			break;
		}
		case Start: {
			if((PINA &0x04) ==0x04) {
				state =Start;
			}
			else {
				state =Start1;
			}
			break;
		}
		case Start1: {
			if((PINA &0x02) ==0x02) {
				state =Unlock;
			}
			else if((PINA &0xFF) ==0x00) {
				state =Start1;
			}
			else {
				state =Wait;
			}
			break;
		}
		case Unlock: {
			state =Wait;
			break;
		}
		case Lock: {
			state =Wait;
			break;
		}
	}
	switch(state) {
		case Lock: {
			PORTB =0x00;
			break;
		}
		case Unlock: {
			PORTB =0x01;
			break;
		}
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0X00;
	DDRB =0xFF;
	PORTB =0x00;
    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 0;
}
