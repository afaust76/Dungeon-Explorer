#include "task.h"

void TimerISR(){
    unsigned short i;
    for(i = 0; i < numtasks; i++){
        if(tasks[i].elapsed_time >= tasks[i].period){
            tasks[i].state = tasks[i].TickFct(tasks[i].state);
            tasks[i].elapsed_time = 0;
        }
        tasks[i].elapsed_time += GCD;
    }
}

/* The following code was provided by the University of California, Riverside */

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff(){
	TCCR1B = 0x00;
}

ISR(TIMER1_COMPA_vect){
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0){
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M){
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

/*----------------------------------------------------------------------------*/