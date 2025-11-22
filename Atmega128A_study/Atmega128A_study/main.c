/*
 * Atmega128A_study.c
 *
 * Created: 2025-11-20 오후 9:47:55
 * Author : User
 */

#include "common.h"


int main(void)
{
	init_max7219();

	for( int i = 1; i<9;i++) {
		max7219_send_cmd(i, 0x00);
	}
    while (1) 
    {
		
		max7219_send_cmd(0x03, 0b10000000);

    }
}


