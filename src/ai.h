#ifndef __AI_H__
#define __AI_H__

#include "defs.h"
#include "block.h"

float ai_height_weight;
float ai_line_weight;
float ai_empty_blocks_weight;

void ai_suggest_best_block_location(int board[BOARD_WIDTH][BOARD_HEIGHT]);
void ai_get_skyline(void);
int ai_get_num_empty_blocks(int board[BOARD_WIDTH][BOARD_HEIGHT]);
void ai_move_block_to_best_location(block_t * block);

block_t ai_block;

#endif