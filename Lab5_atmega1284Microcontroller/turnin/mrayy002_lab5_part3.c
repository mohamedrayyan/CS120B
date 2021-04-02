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
#include <util/delay.h>
#endif

enum states{Start, On} state =Start;

unsigned char design[2][7] ={{0x01,0x3,0x07,0x0F,0x1F,0x3F,0x00},
			{0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00}};
unsigned char i =0x00;
unsigned char k =0x00;

void tick() {
	switch(state) {
		case Start: {
			if((~PINA &0x01) ==0x01) {
				state =On;
			}
			else {
				state =Start;
				i =0x00;
				k =0x00;
				PORTC =0x00;
			}
			break;
		}
		case On: {
			if((~PINA &0x01) ==0x01) {
				i++;
			}
			if(i >2) {
				state =Start;
			}
			else {
				state =On;
			}
			break;
		}
	}
	switch(state) {
		case On: {
			PORTC =design[i][k];
			k++;
			if(k >7) {
				k =0x00;
			}
			_delay_ms(100);
			break;
		}
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0X00;
	PORTA =0xFF;
	DDRC =0xFF;
	PORTC =0x00;
    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 0;
}
