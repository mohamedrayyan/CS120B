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
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum State{Start,Incr,Decr,Hold,Reset} state =Start;
unsigned char i =0x00;
void tick() {
	switch(state) {
		case Start: {
			if((~PINA &0x03) ==0x03) {
				state =Reset;
			}
			else if((~PINA &0x03) ==0x01) {
				state =Incr;
			}
			else if((~PINA &0x03) ==0x02) {
				state =Decr;
			}
			else {
				state =Start;
			}
			break;
		}
		case Incr: {
			state =Hold;	
			break;
		}
		case Decr: {
			state =Hold;
			break;
		}
		case Hold: {
			if(((~PINA &0x03) ==0x00)) {
				state =Start;
			}
			else if((~PINA &0x03) ==0x03) {
				state =Reset;
			}
			else {
				if(i >10) {
					if((~PINA &0x01)) {
						state =Incr;
					}
					else if((~PINA &0x02)) {
						state =Decr;
					}
					i =0;
				}
			}
			break;
		}
		case Reset: {
			if((~PINA &0x03) ==0x00) {
				state =Start;
			}
			else if((~PINA &0x03) ==0x03) {
				state =Reset;
			}
			break;
		}
	}
	switch(state) {
		case Incr: {
			if(PINB <9) {
				PORTB =PINB +1;
			}
			break;
		}
		case Decr: {
			if(PINB >0) {
				PORTB =PINB -1;
			}
			break;
		}
		case Reset: {
			PORTB =0x00;
			break;
		}
		case Hold: {
			i++;
		}
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0X00;
	PORTA =0xFF;
	DDRB =0xFF;
	PORTB =0x07;
	TimerSet(100);
	TimerOn();
    /* Insert your solution below */
    while (1) {
	tick();
	while(!TimerFlag);
	TimerFlag =0;
    }
    return 0;
}
