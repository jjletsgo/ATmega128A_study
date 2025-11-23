/*
 * max7219.h
 *
 * Created: 2025-11-22 오후 9:01:02
 *  Author: User
 */ 


#ifndef MAX7219_H_
#define MAX7219_H_
#include "common.h"

#define NUM_MAX7219 4
#define LOAD 0 //load 역할로 사용할 핀 번호


void init_signle_max7219();
void init_cascaded_max7219();
void max7219_send_cmd(uint8_t address, uint8_t data);
void max7219_send_cmd_all(uint8_t address, uint8_t data);




 // 4개면 32열 (이거 팩맨 하려고 만든거)
#define TOTAL_COLS   (NUM_MAX7219 * 8)  
// 오른쪽을 향한 8x8 팩맨 모양 (열 단위로 정의)
static const uint8_t pacman_sprite[8] = {
	0x38, // 00111000
	0x7C, // 01111100
	0xFE, // 11111110
	0xFE, // 11111110
	0xFE, // 11111110
	0x7C, // 01111100
	0x28, // 00101000 (입)
	0x00  // 바닥 빈 줄
};


void max7219_pacman_step(void);

#endif /* MAX7219_H_ */