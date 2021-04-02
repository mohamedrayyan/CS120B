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

enum State{Wait,Unlock,Lock,} state =Wait;
unsigned char k =0x00;
unsigned char code[4] ={0x04,0x01,0x02,0x01};
void tick() {
	switch(state) {
		case Wait: {
//			if(((PINA &0x01) ==0x01) ||((PINA &0x04) ==0x04) ||((PINA &0x02) ==0x02)) {
			if(((PINA &code[k]) ==code[k]) &&((PINA &0xFF) ==code[k])) {
				k++;
				if(k ==3) {
					state =Unlock;
				}
				else {
					state =Wait;
				}
			}
			else if((PINA &0x80) ==0x80) {
				state =Lock;
			}
			else {
				state =Wait;
			}
			break;
		}
/*
		case Start: {
			if((PINA &code[k]) ==code[k]) {
				k++;
			}
			if(k ==3) {
				state =Unlock;
			}
			else {
				state =Wait;
			}
			break;
		}
*/
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
			PORTB =((PINB &0x01) ==0x01)? 0x00: 0x01;
			k =0x00;
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
