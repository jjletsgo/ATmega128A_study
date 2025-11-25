/*
 * common.h
 *
 * Created: 2025-11-21 오후 4:16:22
 *  Author: User
 */ 


#ifndef COMMON_H_
#define COMMON_H_
#define F_CPU 1000000 //대회 상황에 맞게 수정 !!!!!!!!!!!!항상 제일 위에 있어야함!!!!!!
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "interrupt.h"
#include "timer0.h"
#include "timer1.h" 
#include "spi.h"
#include "max7219.h"    


#endif /* COMMON_H_ */