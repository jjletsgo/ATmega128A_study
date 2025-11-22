/*
 * max7219.c
 *
 * Created: 2025-11-22 오후 9:00:49
 *  Author: User
 */ 
#include "max7219.h"


void init_max7219()
{
	SPI_MasterInit();
	DDRB |= (1 << LOAD);
	PORTB |= (1<<LOAD);       // idle high
	
	max7219_send_cmd(0x09, 0x00);
	max7219_send_cmd(0x0A, 0x01);
	max7219_send_cmd(0x0B, 0x07);
	max7219_send_cmd(0x0C, 0x01);
	max7219_send_cmd(0x0F, 0x00);
	

}


void max7219_send_cmd(uint8_t address, uint8_t data)
{
	PORTB &= ~( 1<< LOAD);
	SPI_MasterTransmit(address);
	SPI_MasterTransmit(data);
	PORTB |= ( 1<< LOAD);
}