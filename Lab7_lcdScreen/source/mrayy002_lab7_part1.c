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
#include "io.h"
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum State{Start,Incr,Decr,Hold,Reset} state =Start;
unsigned char i =0x00;
unsigned char k =0x00;
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
			if(k <9) {
				k++;
				LCD_ClearScreen();
				LCD_WriteData(k +'0');
			}
			break;
		}
		case Decr: {
			if(k >0) {
				k--;
				LCD_ClearScreen();
				LCD_WriteData(k +'0');
			}
			break;
		}
		case Reset: {
			k =0x00;
			LCD_ClearScreen();
			LCD_WriteData(k +'0');
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
	DDRC =0xFF;
	PORTC =0x00;
	DDRD =0xFF;
	PORTD =0x00;
	TimerSet(100);
	TimerOn();
    /* Insert your solution below */
	LCD_init();
	LCD_WriteData(48);
    while (1) {
	tick();
	while(!TimerFlag);
	TimerFlag =0;
    }
    return 0;
}
