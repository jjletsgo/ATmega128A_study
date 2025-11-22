/*
 * timer1.c
 *
 * Created: 2025-11-22 오전 1:24:51
 *  Author: User
 */ 

#include "timer1.h"


volatile uint8_t led_flag = 0;

void init_timer1_CTC_mode() {
	TCCR1B |= (1<< WGM12) | (1 << CS12); // CTC모드로 설정, 클럭 분주비 설정
	uint8_t old_sreg = SREG; //ISR 아니므로 수동으로 SREG 저장
	cli(); //Global Interrupt Disable -> 16비트 레지스터 접근 위해서
	OCR1A = (uint16_t)OCR1A_VAL; //OCR1A값 설정
	SREG = old_sreg; //ISR 아니므로 수동으로 SREG 복구
	
}

void init_timer1_FastPWM_mode() {
	uint8_t old_sreg = SREG; //ISR 아니므로 수동으로 SREG 저장
	cli(); //Global Interrupt Disable -> 16비트 레지스터 접근 위해서
	OCR1A = OCR1A_VAL_FOR_8_BIT_FAST_PWM; //OCR1A값 설정
	SREG = old_sreg; //ISR 아니므로 수동으로 SREG 복구
	TCCR1A |= (1<< WGM10) | (1 << COM1A1) ;
	TCCR1B |= (1 << WGM12) | (1 << CS12); // Fast PWM, 8-bit, 클럭 분주비 설정. Top은 0x00FF로 설정됨
	DDRB |= (1 << 5); //PWM 파형 출력 가능하도록 PB5=OC1A를 출력으로 설정
}


void timer1_COMPA_enable() {
	TIMSK |= ( 1<< OCIE1A); //Timer/Counter1, Output Compare A Match Interrupt Enable
}

ISR(TIMER1_COMPA_vect) {
	// 플래그 토글
	led_flag ^= 1;
}

// led_flag를 atomic하게 읽기
uint8_t timer1_get_flag_atomic(void) {
	uint8_t sreg = SREG;  // 현재 SREG 백업
	cli();                // 인터럽트 잠시 비활성화

	uint8_t flag = led_flag;

	SREG = sreg;          // 원래 인터럽트 상태 복원
	return flag;
}