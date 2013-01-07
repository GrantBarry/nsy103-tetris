#ifndef __BOARD_H__
#define __BOARD_H__

#include "defs.h"
#include "block.h"

void b_draw_board(void);

unsigned int b_does_collide(block_t * block);
void b_getSkyline(int board[BOARD_WIDTH][BOARD_HEIGHT], int skyline[BOARD_WIDTH]);
int b_getNumLines(int board[BOARD_WIDTH][BOARD_HEIGHT]);
int b_getNumEmptyBlocks(int board[BOARD_WIDTH][BOARD_HEIGHT]);
void b_drop_block(block_t * block);
void b_remove_lines();
void b_remove_line(int line);

int board[BOARD_WIDTH][BOARD_HEIGHT];

#endif
