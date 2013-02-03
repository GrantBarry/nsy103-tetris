#ifndef __AI_H__
#define __AI_H__

#include "defs.h"
#include "block.h"
#include "board.h"
#include "game.h"

float ai_height_weight;
float ai_line_weight;
float ai_empty_blocks_weight;

void ai_suggest_best_block_location(void);
//void ai_move_block_to_best_location(block_t * block);

block_t ai_block;

#endif