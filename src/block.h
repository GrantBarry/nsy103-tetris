#ifndef __BLOCK_H__
#define __BLOCK_H__


#include "defs.h"

// Describes the Tetris block type
enum block_type {
	i_block,
	l_block,
	o_block,
	s_block,
	t_block
};

typedef struct {
	int x, y; // Coordinates
	int sizeX, sizeY; // Actual size of the block with in the BLOCK_WIDTH and BLOCK_HEIGHT
	int rotation;
	int tab[BLOCK_WIDTH][BLOCK_HEIGHT];
	enum block_type type;
} block_t;


static int BLOCK_I[4][4] = {
	{1,0,0,0},
	{1,0,0,0},
	{1,0,0,0},
	{1,0,0,0}
};

static int BLOCK_L[4][4] = {
	{1,0,0,0},
	{1,0,0,0},
	{1,1,0,0},
	{0,0,0,0}
};

static int BLOCK_O[4][4] = {
	{1,1,0,0},
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0}
};

static int BLOCK_S[4][4] = {
	{0,1,1,0},
	{1,1,0,0},
	{0,0,0,0},
	{0,0,0,0}
};

static int BLOCK_T[4][4] = {
	{1,1,1,0},
	{0,1,0,0},
	{0,0,0,0},
	{0,0,0,0}
};

void bl_copy(block_t block, block_t copy); // Returns a copy of a block_t structure
void bl_reset(void); // Resets the coordinates of a block_t structure
void bl_move_left(void);
void bl_move_right(void);
void bl_move_down(void);
void bl_rotate_left(void);
void bl_rotate_right(void);
void bl_reflect(void);
void bl_draw(void);
void bl_set_i(void);
void bl_set_l(void);
void bl_set_o(void);
void bl_set_s(void);
void bl_set_s(void);
void bl_set_block_type(enum block_type t);
void bl_clean(void);

block_t current_block;

#endif
