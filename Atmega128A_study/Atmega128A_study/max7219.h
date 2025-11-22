/*
 * max7219.h
 *
 * Created: 2025-11-22 오후 9:01:02
 *  Author: User
 */ 


#ifndef MAX7219_H_
#define MAX7219_H_

#include "common.h"
#define LOAD 0 //load 역할로 사용할 핀 번호
void init_max7219();
void max7219_send_cmd(uint8_t address, uint8_t data);

#endif /* MAX7219_H_ */