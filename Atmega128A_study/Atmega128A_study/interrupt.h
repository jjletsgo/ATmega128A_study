/*
 * interrupt.h
 *
 * ATmega128 외부 인터럽트 INT1 관련 헤더
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "common.h"   // 여기 안에 <avr/io.h>, <avr/interrupt.h> 등이 포함되어 있다고 가정함
#include <stdint.h>


// 전역 인터럽트 enable (sei())
void set_global_INT(void);

// INT1 설정 (FALLING EDGE, 플래그 클리어 + enable)
void setup_int1(void);

// int1_flag를 atomic하게 읽기
uint8_t get_flag_atomic(void);

#endif /* INTERRUPT_H_ */
