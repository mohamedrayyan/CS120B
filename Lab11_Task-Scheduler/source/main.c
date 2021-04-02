#include <avr/io.h>
#include <string.h>
#include "io.h"
#include "keypad.h"
#include "scheduler.h"
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//---------------Shared Variables--------------
//char topObs[] ={" #    #      #    #     "};		//Obstacle 1
//char botObs[] ={"   #      #    #      # "};		//Obstacle 2
char topObs[] ={" #     #      #           #    #     "};		//Obstacle 1
char botObs[] ={"   #      #      #          #      # "};		//Obstacle 2

//char topObs[] ={"CS120B is legend wait for is"};		//Obstacle 1
//char botObs[] ={"#    # #   #   #    #  #   #"};		//Obstacle 2
unsigned char pos =3;
unsigned char pause =0;
unsigned char over =0;
//---------------------------------------------
unsigned char coll(unsigned char r, unsigned char c) {
	if((r ==pos) &&(c =='#')) {
		return 1;
	}
	else {
		return 0;
	}
}

int messageTick(int state) {
if(over) {
	switch(state) {
		case 0: {
			LCD_ClearScreen();
			LCD_DisplayString(1,"HURRAY FOR EMBEDDED SYSTEMS");
			state =1;
			break;
		}
	}
	switch(state) {
		case 0: {break;}
		case 1: {
			if(~PINA &0x04) {
				over =0;
				LCD_ClearScreen();
				pos =3;
				LCD_Cursor(pos);
				state =0;
			}
			else {state =1;}
			break;
		}
	}
}
	return state;
}

int pauseTick(int state) {
	switch(state) {
		case 0: {
			if(~PINA &0x04) {
				pause =1;
				state =1;
			}
			break;
		}
		case 1: {
			if(~PINA &0x04) {
				pause =1;
				state =1;
			}
			else {state =2;
			      pause =1;
			}
			break;
		}
		case 2: {
			if(~PINA &0x04) {
				state =3;
				pause =1;
			}
			break;
		}
		case 3: {
			if(~PINA &0x04) {state =3;pause =1;}
			else {state =0;pause =0;};
			break;
		}	break;
	}
	return state;
}
enum obstacles1{display1,display2};
	unsigned char m =0;
	unsigned char q =0;
	unsigned char z =0;
	unsigned char x =0;
	unsigned char y =0;
	unsigned char top =16;
	unsigned char bot =32;
void reset() {
	m =0;q=0;z=0;x=0;y=0;top=16;bot=32;
}
int obs1Tick(int state) {
	unsigned char len =strlen(topObs);
if(!pause &&!over) {
	switch(state) {
		case 0: {
			if(top >=1) {
				state =0;
			}
			else if(top <1) {
				q =0;
				state =1;
			}
			break;
		}
		case 1: {
			if(z ==len) {
				reset();
				state =0;
			}
			break;
		}
	}
	switch(state) {
		case 0: {
			x =top; y=bot;
			for(q =0; q <m; q++,x++,y++) {
				LCD_Cursor(x);
				LCD_WriteData(topObs[q]);	//top
				if((x ==3)) {
					if(coll(3,topObs[q])) {
						over =1;
						state =0;
						reset();
						return state;
					}
				}
				LCD_Cursor(y);
				LCD_WriteData(botObs[q]);	//bot
				if((y ==19)) {
					if(coll(19,botObs[q])) {
						over =1;
						state =0;
						reset();
						return state;
					}
				}
			}
			LCD_Cursor(pos);
			top--;bot--;
			if(m <len) {m++;}
			break;
		}
		case 1: {
			z++;	//z =0;
			x =1;
			y =17;
			for(q =z; ((q <m) &&(x !=17) &&(y !=33)); q++,x++,y++) {
				LCD_Cursor(x);
				LCD_WriteData(topObs[q]);
				if((x ==3)) {
					if(coll(3,topObs[q])) {
						over =1;
						state =0;
						reset();
						return state;
					}
				}
				LCD_Cursor(y);
				LCD_WriteData(botObs[q]);
				if((y ==19)) {
					if(coll(19,botObs[q])) {
						over =1;
						state =0;
						reset();
						return state;
					}
				}
			}
			LCD_Cursor(pos);
			if(m <len) {m++;}
			break;
		}
	}
}
	return state;
}
enum player{start,dispPlyr};
int playerTick(int state) {
if(!pause &&!over) {
	switch(state) {
		case 0: {
			pos =3;
			LCD_Cursor(pos);
			state =1;
			break;
		}
		case 1: {
			state =1;
			break;
		}
	}
	switch(state) {
		case 0: {break;}
		case 1: {
			if(~PINA &0x01) {
				pos =3;
				LCD_Cursor(pos);
			}
			else if(~PINA &0x02) {
				pos =19;
				LCD_Cursor(pos);
			}
			break;
		}
	}
}
	return state;
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB =0xFF;
	PORTB =0x00;
	DDRD =0xFF;
	PORTB =0x00;
	DDRA =0x00;
	PORTA =0xFF;
    /* Insert your solution below */
	static task task1,task2,task3,task4;
	task *tasks[] ={&task1,&task2,&task3,&task4};
	unsigned char numTasks =sizeof(tasks)/sizeof(task*);

	task1.state =0;
	task1.period =1;
	task1.elapsedTime =task1.period;
	task1.TickFct =&playerTick;
//--------------------------------------------
	task2.state =0;
	task2.period =350;
	task2.elapsedTime =task2.period;
	task2.TickFct =&obs1Tick;
//--------------------------------------------
	task3.state =0;
	task3.period =150;
	task3.elapsedTime =task3.period;
	task3.TickFct =&pauseTick;
//--------------------------------------------
	task4.state =0;
	task4.period =1;
	task4.elapsedTime =task4.period;
	task4.TickFct =&messageTick;
//--------------------------------------------
	unsigned long GCD =tasks[0]->period;
	for(unsigned char i =1; i <numTasks; i++) {
		GCD =findGCD(GCD,tasks[i]->period);
	}

	TimerSet(GCD);
	TimerOn();
	LCD_init();

	while(1) {
		for(unsigned char i =0; i <numTasks; i++) {
			if(tasks[i]->elapsedTime ==tasks[i]->period) {
				tasks[i]->state =tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime =0;
			}
			tasks[i]->elapsedTime +=GCD;
		}
		while(!TimerFlag);
		TimerFlag =0;
	}
	return 0;
}
