
#include "block.h"

void bl_set_max_sizes(block_t *block) {
	int x, y;

	block->sizeX = 0;
	block->sizeY = 0;
	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			if (block->tab[x][y] == 1 && block->sizeX <= x) {
				block->sizeX = x + 1;
			}
			if (block->tab[x][y] == 1 && block->sizeY <= y) {
				block->sizeY = y + 1;
			}
		}
	}
}

void bl_set_block_type(block_t *block, enum block_type t) {

	int x, y, offset;
	offset = 4 * (int)(block->rotation / 90);

	if (!block) {
		return;
	}

	block->type = t;

	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			switch (t) {
			case i_block:
				block->tab[x][y] = BLOCK_I[offset + y][x];
				break;
			case l_block:
				block->tab[x][y] = BLOCK_L[offset + y][x];
				break;
			case o_block:
				block->tab[x][y] = BLOCK_O[offset + y][x];
				break;
			case s_block:
				block->tab[x][y] = BLOCK_S[offset + y][x];
				break;
			case t_block:
				block->tab[x][y] = BLOCK_T[offset + y][x];
				break;
			case z_block:
				block->tab[x][y] = BLOCK_Z[offset + y][x];
				break;
			case u_block:
				block->tab[x][y] = BLOCK_U[offset + y][x];
				break;
			case big_l_block:
				block->tab[x][y] = BLOCK_BIG_L[offset + y][x];
				break;
			case big_t_block:
				block->tab[x][y] = BLOCK_BIG_T[offset + y][x];
				break;
			}
		}
	}

	bl_set_max_sizes(block);
}

void bl_reset(block_t *block) {
	if (!block) {
		return;
	}

	block->x = BOARD_WIDTH / 2;
	block->y = 0;
	block->rotation = 0;
	block->reflected = 0;
}

void bl_move_left(block_t *block) {
	if (!block) {
		return;
	}

	if (block->x > 0) {
		block->x--;
	}
}

void bl_move_right(block_t *block) {
	if (!block) {
		return;
	}

	if (block->x < BOARD_WIDTH - block->sizeX) {
		block->x++;
	}
}

void bl_move_down(block_t *block) {
	if (!block) {
		return;
	}

	if (block->y <= ((BOARD_HEIGHT - 1) - block->sizeY)) {
		block->y++;
	}
}

void bl_rotate_clockwise(block_t *block) {
	if (!block) {
		return;
	}

	if (block->type == o_block) {
		// No rotation needed
		return;
	}

	if (block->rotation == 270) {
		block->rotation = 0;
	} else {
		block->rotation += 90;
	}

	bl_set_block_type(block, block->type);
}

void bl_rotate_anti_clockwise(block_t *block) {
	if (!block) {
		return;
	}

	if (block->type == o_block) {
		// No rotation needed
		return;
	}

	if (block->rotation == 0) {
		block->rotation = 270;
	} else {
		block->rotation -= 90;
	}

	bl_set_block_type(block, block->type);
}

void bl_reflect(block_t *block) {
	block_t copy;
	int x, y;

	if (!block) {
		return;
	}

	if (block->type == o_block || block->type == i_block) { // No reflection needed
		return;
	}

	memcpy(&copy, block, sizeof(copy));

	if (block->reflected == 0) {
		block->reflected = 1;
	} else {
		block->reflected = 0;
	}

	for (y = 0; y < block->sizeY; y++) {
		for (x = 0; x < block->sizeX; x++) {
			block->tab[(block->sizeX-1)-x][y] = copy.tab[x][y];
		}
	}
	bl_set_max_sizes(block);
}

void bl_draw(const block_t *block) {
	int x, y;

	if (!block) {
		return;
	}

	for (y = 0; y < block->sizeY; y++) {
		for (x = 0; x < block->sizeX; x++) {
			if (block->tab[x][y] == 1) {
				mvprintw(block->y + y, block->x + x + BOARD_DRAW_OFFSET, "*");
			}
		}
	}
}

void bl_set_current_block(enum block_type t) {
	bl_set_block_type(&current_block, t);
}

void bl_set_next_block(enum block_type t) {
	bl_set_block_type(&next_block, t);
}

// current_block becomes next_block and next_block is set
void bl_push_next_block(enum block_type t) {
	bl_set_current_block(next_block.type);
	bl_set_next_block(t);
}