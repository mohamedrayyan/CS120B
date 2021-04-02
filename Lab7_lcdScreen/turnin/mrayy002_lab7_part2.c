
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
#include "io.h"
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start,Freeze,Pressed,Pressed1, Victory} state;
unsigned char seq[9] ={1,2,4,2};
unsigned char i =0x00;
unsigned char k =0x00;
unsigned char p =0x00;

void victory() {
	LCD_ClearScreen();
	LCD_DisplayString(1,"You WIN");
}
void dispScore() {	
	LCD_ClearScreen();
	LCD_DisplayString(1,"Score: ");
	LCD_WriteData(k +'0');
}
void tick() {
	switch(state) {
		case Start: {
			if((~PINA &0x01)) {
				state =Pressed;
			}
			else {
				state =Start;
				PORTB =seq[i];
			}
			break;
		}
		case Freeze: {
			if(PINB &0x02) {
				if(k <9) {
					k++;
				}
			}
			else {
				if(k >0) {
					k--;
				}
			}
			dispScore();
			if(k ==9) {
				state =Victory;
				k =0;
			}
			else {
				state =Start;
			}
			break;
		}
		case Pressed: {
			if((~PINA &0x01)) {
				state =Pressed;
			}
			else {
				state =Freeze;
			}
			break;
		}
		case Pressed1: {
			if((~PINA &0x01)) {
				state =Pressed1;
			}
			else {
				state =Start;
				i =-1;
			}
			break;
		}
		case Victory: {
			if(p >20) {
				state =Start;
				dispScore();
				p =0;
			}
			else if(p %5 ==0) {
				victory();
				PORTB =0x07;
			}
			else {
				LCD_ClearScreen();
				PORTB =0x00;
			}
			break;
		}
	}
	switch(state) {
		case Start: {
			PORTB =seq[i];
			i++;
			if(i >=4) {
			 	i =0;
			}
			break;
		}
		case Freeze: {
			dispScore();
			break;
		}
		case Victory: {
			p++;
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
	DDRC =0xFF;
	PORTC =0x00;
	DDRD =0xFF;
	PORTD =0x00;
    /* Insert your solution below */
	LCD_init();
	TimerSet(300);
	TimerOn();
	state =Start;
	dispScore();
    while (1) {
	    tick();
	    while(!TimerFlag);
	    TimerFlag =0;
    }
    return 1;
}
