/*
 * adc.h
 *
 * Created: 2025-11-22 오후 5:12:46
 *  Author: User
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "common.h"
void init_ADC_Free_Running_Mode();
void read_adc_val (uint16_t *adc_val);

#endif /* ADC_H_ */