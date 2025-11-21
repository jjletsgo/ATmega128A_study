/*
 * interrupt.c
 *
 * ATmega128 외부 인터럽트 INT1 설정 및 ISR
 */

#include "interrupt.h"

// ISR과 main에서 같이 쓰는 플래그
volatile uint8_t int1_flag = 0;

// 전역 인터럽트 enable
void set_global_int(void) {
    sei();
}

// INT1 설정: PD1(INT1), Falling edge 트리거
void setup_int1(void) {
    // 여기서는 글로벌 인터럽트는 건드리지 않음 (main에서 set_global_int()로 켜게 함)

    // 1) INT1 잠깐 disable
    EIMSK &= ~(1 << INT1);

    // 2) 트리거 조건 설정: Falling edge
    //    ISC11 = 1, ISC10 = 0
    EICRA &= ~((1 << ISC11) | (1 << ISC10)); // 둘 다 0으로 클리어
    EICRA |=  (1 << ISC11);                  // ISC11만 1로 세트

    // 3) 이전에 남아 있을 수 있는 INTF1 플래그 클리어
    EIFR |= (1 << INTF1);

    // 4) INT1 enable
    EIMSK |= (1 << INT1);
}

// INT1 인터럽트 서비스 루틴
ISR(INT1_vect) {
    // 플래그 토글
    int1_flag ^= 1;
}

// int1_flag를 atomic하게 읽기
uint8_t get_flag_atomic(void) {
    uint8_t sreg = SREG;  // 현재 SREG 백업
    cli();                // 인터럽트 잠시 비활성화

    uint8_t flag = int1_flag;

    SREG = sreg;          // 원래 인터럽트 상태 복원
    return flag;
}
