#ifndef __BOARD_H__
#define __BOARD_H__

#include "defs.h"
#include "block.h"

void b_draw_board(void);
unsigned int b_does_collide(block_t * block);
int b_get_num_lines(void);
int b_get_num_empty_blocks(void);
void b_drop_block(block_t * block);
void b_remove_lines();
void b_remove_line(int line);
int b_is_empty_line(int line);

int board[BOARD_WIDTH][BOARD_HEIGHT];

#endif
