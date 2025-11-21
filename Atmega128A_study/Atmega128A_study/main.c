/*
 * Atmega128A_study.c
 *
 * Created: 2025-11-20 오후 9:47:55
 * Author : User
 */

#include "common.h"

int main(void)
{
    DDRD |= (1<<1);
	PORTD &= ~(1<<1);
	set_global_INT();	
	void init_timer0_normal_mode_OVF(); 
	timer_ms led_timer;
	uint8_t led_on_flag = 0;
    while (1) 
    {
		if(timer_delay_ms(&led_timer, 500)) {
			led_on_flag^=1;
		} 
		if (led_on_flag) {
			PORTD |= (1 << 1);
		} else PORTD &= ~(1<<1);
	}
}
