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
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned char i =0x00;
void ADC_init() {
	ADCSRA |=(1 <<ADEN) |(1 <<ADSC) |(1 <<ADATE);
}	
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0x00;
	DDRB =0xFF;
	PORTB =0x00;
	DDRD =0xFF;
	PORTD =0x00;
    /* Insert your solution below */
	ADC_init();
	PORTB =0x01;
	unsigned short max =0x1C2;
	unsigned char hld =(max /8);
	unsigned char i =0x00;
	unsigned char k =0x00;
    while (1) {
	unsigned short adc =ADC;
	for(i =1, k =7; i <=8; i++, k--) {
		if(adc <=i *hld) {
			PORTB =(0xFF >>(k));
			i =9;
		}
	}
    }
    return 1;
}
