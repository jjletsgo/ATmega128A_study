/*
 * Atmega128A_study.c
 *
 * Created: 2025-11-20 오후 9:47:55
 * Author : User
 */

#include "common.h"


int main(void)
{
	init_cascaded_max7219();

	
    while (1) 
    {
		max7219_pacman_step(); // 한 스텝 이동
		_delay_ms(80);         // 이동 속도 조절 (느리게/빠르게 바꾸고 싶으면 이 값만 조절)

    }
}


