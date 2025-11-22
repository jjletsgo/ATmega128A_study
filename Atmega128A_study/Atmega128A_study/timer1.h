/*
 * timer1.h
 *
 * Created: 2025-11-22 오전 1:25:05
 *  Author: User
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_
#include "common.h"

//1 마이크로초당 클럭이 몇 주기 들어오는지
#define PRESCALE_VALUE 256 //분주비 값
#define CLK_TIMER1 (F_CPU/PRESCALE_VALUE) //타이머1로 들어가는 클럭의 주파수
#define COMPARE_MATCH_INT_MS_INTERVAL 500 //ms단위 비교일치 인터럽트 발생 주기
#define OCR1A_VAL ( (uint16_t)( (CLK_TIMER1 * COMPARE_MATCH_INT_MS_INTERVAL / 1000UL) - 1UL ) )


void init_timer1_CTC_mode();
void timer1_COMPA_enable();
uint8_t timer1_get_flag_atomic(void);

#endif /* TIMER1_H_ */