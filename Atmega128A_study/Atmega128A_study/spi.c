/*
 * spi.c
 *
 * Created: 2025-11-22 오후 9:22:37
 *  Author: User
 */ 

#include "spi.h"

void SPI_MasterInit(void)
{
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	/* Set MOSI and SCK output, all others input */
	DDRB|= ( 1<< 0) | (1 << 1) | (1 << 2); //SS,SCK,MOSI를 OUTPUT으로 설정
	PORTB |= (1<<0);  // SS idle high
}
void SPI_MasterTransmit(uint8_t data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));   
}
