#ifndef __BOARD_H__
#define __BOARD_H__

#include "defs.h"
#include "block.h"
#include "game.h"

void b_draw_board(void);
unsigned int b_does_collide(block_t * block);
int b_get_num_lines(void);
int b_get_num_empty_blocks(void);
void b_drop_block(block_t * block);
unsigned int b_remove_lines(void);
void b_remove_line(int line);
int b_is_full_line(int line);
void b_insert_line(int data[BOARD_WIDTH]);

int board[BOARD_WIDTH][BOARD_HEIGHT];

#endif
