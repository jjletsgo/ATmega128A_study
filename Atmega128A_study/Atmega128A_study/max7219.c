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

// 팩맨
// world[0..TOTAL_COLS-1] : 전체 32열 화면 버퍼 (각 byte가 세로 8픽셀)
static void max7219_update_from_world(uint8_t world[TOTAL_COLS])
{
	for (uint8_t col = 0; col < 8; col++) {   // col = 0..7 (MAX7219의 digit 1~8)
		PORTB &= ~(1 << LOAD);               // CS low

		// 가장 먼 칩부터 → 가장 가까운 칩 순으로 전송
		for (int chip = NUM_MAX7219 - 1; chip >= 0; chip--) {
			uint8_t addr = col + 1;                  // digit 주소 = 1~8
			uint8_t data = world[chip * 8 + col];    // 이 칩의 이 열에 해당하는 패턴

			SPI_MasterTransmit(addr);
			SPI_MasterTransmit(data);
		}

		PORTB |= (1 << LOAD);                // CS high → 4개 칩이 동시에 래치
	}
}

// 팩맨을 한 칸씩 오른쪽으로 옮기면서 그리는 함수 (한 번 호출 = 한 스텝)
void max7219_pacman_step(void)
{
	static int offset = -8;                  // 처음엔 화면 왼쪽 밖에서 시작
	uint8_t world[TOTAL_COLS];

	// 화면 전체 클리어
	for (int i = 0; i < TOTAL_COLS; i++) {
		world[i] = 0x00;
	}

	// pacman_sprite를 offset 위치에 그리기
	for (int col = 0; col < 8; col++) {
		int x = offset + col;                // 전체 0~(TOTAL_COLS-1) 중 위치

		if (x >= 0 && x < TOTAL_COLS) {
			world[x] = pacman_sprite[col];
		}
	}

	// 실제 MAX7219들에 전송
	max7219_update_from_world(world);

	// 다음 스텝으로 이동
	offset++;
	if (offset > TOTAL_COLS) {
		offset = -8;                         // 다시 왼쪽 밖에서 재시작
	}
}

//팩맨