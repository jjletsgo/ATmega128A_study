/*
 * Atmega128A_study.c
 *
 * Created: 2025-11-20 오후 9:47:55
 * Author : User
 */

#include "common.h"

int main(void)
{
	uint16_t adc_val;
	DDRD|=(1 << 2);
	init_ADC_Free_Running_Mode();

    while (1) 
    {
		read_adc_val(&adc_val);
		if(adc_val < 512) {
			PORTD |= ( 1<< 2);
		} else PORTD &= ~( 1<< 2);
    }
}
