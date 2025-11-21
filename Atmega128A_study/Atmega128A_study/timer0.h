/*
 * timer0.h
 *
 * Created: 2025-11-21 오후 10:54:59
 *  Author: User
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_
#include "common.h"
//1 마이크로초당 클럭이 몇 주기 들어오는지 
#define CLOCKS_PER_MICRO ( F_CPU / 1000000L )
#define PRESCALE_VALUE 32
#define TIMER0_SIZE 256
//해당 클럭이 총 몇 마이크로초인지 반환
#define CLOCKS_TO_MICROSECONDS(a) ( (a) / CLOCKS_PER_MICRO )
// Timer0의 분주비가 8이다 -> 클럭 주파수가 1/8 배되므로, 초당 입력되는 펄스의 수가 기존(16Mhz기준)의 1/8배된다.
// 이는 카운터 입장에서 같은 수의 클럭을 셀 때, 시스템 클럭을 16Mhz로 그대로 쓰면서 펄스를 8배로 세는것과 동일하다.
// 따라서 단순히 256이 아니라 8*256을 전달해야 오버플로 인터럽트 발생까지
// 몇 마이크로초 걸리는지를 반환해준다.
#define MICROSECONDS_PER_TIMER0_OVERFLOW ( CLOCKS_TO_MICROSECONDS(PRESCALE_VALUE*TIMER0_SIZE))
// 오버플로 인터럽트 발생까지 몇 밀리초 걸리는지 (밀리 단위 몫) 
#define MILLIS_INCREMENT_PER_OVERFLOW ( MICROSECONDS_PER_TIMER0_OVERFLOW / 1000 )
// 오버플로 인터럽트 발생까지 밀리초 단위 증가 제외하고 남은 마이크로초 단위 (마이크로단위의 아주작은 나머지)
#define MICROS_INCREMENT_PER_OVERFLOW ( MICROSECONDS_PER_TIMER0_OVERFLOW % 1000 )

typedef struct {
	uint16_t is_init_done; // 첫 번째 호출인지 여부확인용 플래그변수 (C99 표준에서는 초기값 설정 불가)
	unsigned long ms_time; // ms 시간 저장할 변수
} timer_ms;

// 함수 프로토타입
uint8_t timer_delay_ms(timer_ms *timer, uint16_t delay_ms);
void init_timer0_ovf();
unsigned long millis();
uint16_t secs();  // secs() 함수 선언 추가
void reset_timer0();

#endif /* TIMER0_H_ */


