/*
 * Atmega128A_study.c
 *
 * Created: 2025-11-20 오후 9:47:55
 * Author : User
 */

#include "common.h"
#include "interrupt.h"

int main(void)
{
    // PD1: INT1 입력 (외부 풀업 사용한다고 했으니 내부 풀업은 안 켬)
    DDRD &= ~(1 << PD1);      // PD1 입력 설정
    PORTD |= (1 << PD1);  // 내부 풀업 ON

    // PD2: LED 출력
    DDRD |= (1 << PD2);
    PORTD &= ~(1 << PD2);     // 처음에는 LED OFF

    // INT1 설정
    setup_int1();

    // 전역 인터럽트 활성화
    set_global_int();

    while (1) 
    {
        // int1_flag 값에 따라 LED 제어
        if (get_flag_atomic()) {
            PORTD |= (1 << PD2);   // flag == 1 → LED ON
        } else {
            PORTD &= ~(1 << PD2);  // flag == 0 → LED OFF
        }
    }
}
