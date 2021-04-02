/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "pwm.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states{start,cF, dF, eF} state =start;

void tick() {
	unsigned char pina =~PINA;
	switch(state) {
		case start: {
			if((pina &0x0F) ==0x02) {
				state =cF;
			}
			else if((pina &0x0F) ==0x04) {
				state =dF;
			}
			else if((pina &0x0F) ==0x08) {
				state =eF;
			}
			else {
				set_PWM(0.0);
				PORTD =0x00;
			}
			break;
		}
		case cF: {
			if((pina &0x0F) ==0x02) {
				state =cF;
				PORTD =0x01;
				set_PWM(261.63);
			}
			else {
				state =start;
			}
			break;
		}
		case dF: {
			if((pina &0x0F) ==0x04) {
				state =dF;
				PORTD =0x01;
				set_PWM(293.66);
			}
			else {
				state =start;
			}
			break;
		}
		case eF: {
			if((pina &0x0F) ==0x08) {
				state =eF;
				PORTD =0x01;
				set_PWM(329.63);
			}
			else {
				state =start;
			}
			break;
		}
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0x00;
	PORTA =0xFF;
	DDRB =0xFF;
	PORTB =0x00;
	DDRD =0xFF;
	PORTD =0x00;
    /* Insert your solution below */
	PWM_on();
    while (1) {
	tick();
    }
    return 1;
}
