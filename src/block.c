
#include "block.h"

void bl_set_max_sizes(block_t * block) {
	int x, y;

	block->sizeX = 0;
	block->sizeY = 0;
	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			if (block->tab[x][y] == 1 && block->sizeX <= x) {
				block->sizeX = x+1;
			}
			if (block->tab[x][y] == 1 && block->sizeY <= y) {
				block->sizeY = y+1;
			}
		}
	}
}

void bl_set_block_type(enum block_type t) {

	int x, y, offset;
	offset = 4 * (int)(current_block.rotation / 90);

	current_block.type = t;

	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			switch (t) {
				case i_block:
					current_block.tab[x][y] = BLOCK_I[offset + y][x];
					break;
				case l_block:
					current_block.tab[x][y] = BLOCK_L[offset + y][x];
					break;
				case o_block:
					current_block.tab[x][y] = BLOCK_O[offset + y][x];
					break;
				case s_block:
					current_block.tab[x][y] = BLOCK_S[offset + y][x];
					break;
				case t_block:
					current_block.tab[x][y] = BLOCK_T[offset + y][x];
					break;
			}
		}
	}

	bl_set_max_sizes(&current_block);
}

void bl_reset(block_t * block) {
	if (!block) {
		return;
	}

	block->x = BOARD_WIDTH / 2;
	block->y = 0;
	block->rotation = 0;
}

void bl_move_left(block_t * block) {
	if (!block) {
		return;
	}

	if (block->x > 0)
		block->x--;
}

void bl_move_right(block_t * block) {
	if (!block) {
		return;
	}

	if (block->x < ((BOARD_WIDTH)-block->sizeX))
		block->x++;
}

void bl_move_down(block_t * block) {
	if (!block) {
		return;
	}

	if (block->y <= ((BOARD_HEIGHT-1)-block->sizeY)) {
		block->y++;
	}
}

void bl_rotate_right(block_t * block) {
	if (!block) {
		return;
	}

	if (block->type == o_block) { // No rotation needed
		return;
	}

	if (block->rotation == 270) {
		block->rotation = 0;
	}
	else {
		block->rotation += 90;
	}

	bl_set_block_type(block->type);
}

void bl_rotate_left(block_t * block) {
	if (!block) {
		return;
	}

	if (block->type == o_block) { // No rotation needed
		return;
	}

	if (block->rotation == 0) {
		block->rotation = 270;
	}
	else {
		block->rotation -= 90;
	}

	bl_set_block_type(block->type);
}

void bl_reflect(block_t * block) {
	block_t copy;
	int x, y;

	if (!block) {
		return;
	}

	if (block->type == o_block || block->type == i_block) { // No reflection needed
		return;
	}

	memcpy(&copy, block, sizeof(copy));

	for (y = 0; y < block->sizeY; y++) {
		for (x = 0; x < block->sizeX; x++) {
			block->tab[(block->sizeX-1)-x][y] = copy.tab[x][y];
		}
	}
	bl_set_max_sizes(block);
}

void bl_draw(const block_t * block) {
	int x, y;

	if (!block) {
		return;
	}

	for (y = 0; y < block->sizeY; y++) {
		for (x = 0; x < block->sizeX; x++) {
			if (block->tab[x][y] == 1) {
				mvprintw(block->y+y, block->x+x+BOARD_DRAW_OFFSET, "*");
			}
		}
	}
}