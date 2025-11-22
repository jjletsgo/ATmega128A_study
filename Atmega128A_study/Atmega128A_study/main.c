/*
 * Atmega128A_study.c
 *
 * Created: 2025-11-20 오후 9:47:55
 * Author : User
 */

#include "common.h"

void init_port(void);

void init_port() {
	DDRD |= (1 << 2);
	PORTD &= ~(1 << 2);
	
}


int main(void)
{
	init_timer1_FastPWM_mode();
	sei();
    while (1) 
    {
    }
}

