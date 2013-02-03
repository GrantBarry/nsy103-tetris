#ifndef __BLOCK_H__
#define __BLOCK_H__


#include "defs.h"

// Describes the Tetris block type
enum block_type {
	i_block,
	o_block,
	l_block,
	t_block,
	s_block,
	z_block,
	u_block,
	big_l_block,
	big_t_block
};

typedef struct {
	int x, y; // Coordinates
	int sizeX, sizeY; // Actual size of the block with in the BLOCK_WIDTH and BLOCK_HEIGHT
	int rotation;
	int reflected;
	int tab[BLOCK_WIDTH][BLOCK_HEIGHT];
	enum block_type type;
} block_t;


static int BLOCK_I[16][4] = {
	{1, 0, 0, 0},
	{1, 0, 0, 0},
	{1, 0, 0, 0},
	{1, 0, 0, 0},

	{1, 1, 1, 1},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},

	{1, 0, 0, 0},
	{1, 0, 0, 0},
	{1, 0, 0, 0},
	{1, 0, 0, 0},

	{1, 1, 1, 1},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
};

static int BLOCK_L[16][4] = {
	{1, 0, 0, 0},
	{1, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},

	{1, 1, 1, 0},
	{1, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},

	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0},

	{0, 0, 1, 0},
	{1, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
};

static int BLOCK_O[16][4] = {
	{1, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},

	{1, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},

	{1, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},

	{1, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
};

static int BLOCK_S[16][4] = {
	{0, 1, 1, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},

	{1, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0},

	{0, 1, 1, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},

	{1, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}
};

static int BLOCK_T[16][4] = {
	{1, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},

	{0, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0},

	{0, 1, 0, 0},
	{1, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},

	{1, 0, 0, 0},
	{1, 1, 0, 0},
	{1, 0, 0, 0},
	{0, 0, 0, 0}
};

static int BLOCK_Z[16][4] = {
	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 0},

	{0, 0, 0, 1},
	{1, 1, 1, 1},
	{1, 0, 0, 0},
	{0, 0, 0, 0},

	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 1, 1, 0},

	{0, 0, 0, 1},
	{1, 1, 1, 1},
	{1, 0, 0, 0},
	{0, 0, 0, 0}
};

static int BLOCK_U[16][4] = {
	{1, 1, 0, 0},
	{1, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},

	{1, 1, 1, 0},
	{1, 0, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},

	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 0},

	{1, 0, 1, 0},
	{1, 1, 1, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
};

static int BLOCK_BIG_L[16][4] = {
	{1, 0, 0, 0},
	{1, 0, 0, 0},
	{1, 1, 1, 0},
	{0, 0, 0, 0},

	{1, 1, 1, 0},
	{1, 0, 0, 0},
	{1, 0, 0, 0},
	{0, 0, 0, 0},

	{1, 1, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 0},

	{0, 0, 1, 0},
	{0, 0, 1, 0},
	{1, 1, 1, 0},
	{0, 0, 0, 0}
};

static int BLOCK_BIG_T[16][4] = {
	{1, 1, 1, 0},
	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0},

	{0, 0, 1, 0},
	{1, 1, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 0},

	{0, 1, 0, 0},
	{0, 1, 0, 0},
	{1, 1, 1, 0},
	{0, 0, 0, 0},

	{1, 0, 0, 0},
	{1, 1, 1, 0},
	{1, 0, 0, 0},
	{0, 0, 0, 0}
};

void bl_copy(block_t block, block_t copy); // Returns a copy of a block_t structure
void bl_reset(block_t *block);  // Resets the coordinates of a block_t structure
void bl_set_block_type(block_t *block, enum block_type t);
void bl_set_max_sizes(block_t *block);
void bl_move_left(block_t *block);
void bl_move_right(block_t *block);
void bl_move_down(block_t *block);
void bl_rotate_clockwise(block_t *block);
void bl_rotate_anti_clockwise(block_t *block);
void bl_reflect(block_t *block);
void bl_draw(const block_t *block);
void bl_set_current_block(enum block_type t);
void bl_set_next_block(enum block_type t);
void bl_push_next_block(enum block_type t); // current_block becomes next_block and next_block is set

block_t current_block;
block_t next_block;

#endif
