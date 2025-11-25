/*
 * max7219.c
 *
 * Created: 2025-11-22 오후 9:00:49
 *  Author: User
 */ 
#include "max7219.h"


void init_single_max7219()
{
	SPI_MasterInit();
	DDRB |= (1 << LOAD);
	PORTB |= (1<<LOAD);       // idle high
	
	max7219_send_cmd(0x09, 0x00);
	max7219_send_cmd(0x0A, 0x01);
	max7219_send_cmd(0x0B, 0x07);
	max7219_send_cmd(0x0C, 0x01);
	max7219_send_cmd(0x0F, 0x00);
	
	for( int i = 1; i<9;i++) {
		max7219_send_cmd(i, 0x00);
	}
}

void init_cascaded_max7219()
{
    SPI_MasterInit();
    DDRB |= (1<<LOAD);
    PORTB |= (1<<LOAD); // idle high

    max7219_send_cmd_all(0x09, 0x00); // no decode
    max7219_send_cmd_all(0x0A, 0x01); // intensity
    max7219_send_cmd_all(0x0B, 0x07); // scan limit = 8
    max7219_send_cmd_all(0x0C, 0x01); // shutdown off
    max7219_send_cmd_all(0x0F, 0x00); // display test off

    // 모든 칩의 digit 1~8 클리어
    for (int d = 1; d <= 8; d++) {
	    max7219_send_cmd_all(d, 0x00);
    }
}


void max7219_send_cmd(uint8_t address, uint8_t data)
{
	PORTB &= ~( 1<< LOAD);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(data);
	PORTB |= ( 1<< LOAD);
}



void max7219_send_cmd_all(uint8_t address, uint8_t data)
{
	PORTB &= ~(1<<LOAD);          // CS low

	for (int i = 0; i < NUM_MAX7219; i++) {
		SPI_MasterTransmit(address);
		SPI_MasterTransmit(data);
	}

	PORTB |= (1<<LOAD);           // CS high → 4개 칩이 동시에 래치
}
