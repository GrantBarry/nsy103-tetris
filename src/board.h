#ifndef __BOARD_H__
#define __BOARD_H__

#include "defs.h"
#include "block.h"

void b_draw_board(void);
unsigned int b_does_collide(block_t * block);
int b_get_num_lines(int board[BOARD_WIDTH][BOARD_HEIGHT]);
int b_get_num_empty_blocks(int board[BOARD_WIDTH][BOARD_HEIGHT]);
void b_drop_block(block_t * block);
void b_remove_lines();
void b_remove_line(int line);

int board[BOARD_WIDTH][BOARD_HEIGHT];
/*
typedef struct board_t {
	int board[BOARD_WIDTH][BOARD_HEIGHT];
} board_t;
*/
#endif
