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
	init_port();
	init_timer1_CTC_mode();
	timer1_COMPA_enable();
	sei();
	

    while (1) 
    {
        // int1_flag 값에 따라 LED 제어
        if (timer1_get_flag_atomic()) {
            PORTD |= (1 << PD2);   // flag == 1 → LED ON
        } else {
            PORTD &= ~(1 << PD2);  // flag == 0 → LED OFF
        }
    }
}

