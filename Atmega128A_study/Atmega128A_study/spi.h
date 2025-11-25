
/*
 * spi.h
 *
 * Created: 2025-11-22 오후 9:22:46
 *  Author: User
 */ 


#ifndef SPI_H_
#define SPI_H_
#include "common.h"

void SPI_MasterInit(void);
void SPI_MasterTransmit(uint8_t data);


#endif /* SPI_H_ */
