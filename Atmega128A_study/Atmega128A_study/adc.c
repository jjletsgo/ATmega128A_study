/*
 * adc.c
 *
 * Created: 2025-11-22 오후 5:12:27
 *  Author: User
 */ 
#include "adc.h"

void init_ADC_Free_Running_Mode() {
	DDRF &= ~(1<<1);
	PORTF |= (1 << 1);
	ADMUX |= (1<<REFS0) | (1 << MUX0); //VREF를 AVCC로 설정, 채널을 1로 설정, Right adjusted
	ADCSRA |= (1 << ADEN) | (1 << ADFR) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADSC);
}

void read_adc_val (uint16_t *adc_val) {
	uint8_t Low_Byte = ADCL; //8bit read이니 자동 atomic함. ADCL 읽는 순간 ADCH는 LOCK됨.
	uint8_t High_Byte = ADCH; //ADCH 읽었으니 ADCH LOCK 해제
	*adc_val = (((uint16_t)High_Byte) << 8) | Low_Byte;
}