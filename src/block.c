
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

void bl_reset() {
	current_block.x = BOARD_WIDTH / 2;
	current_block.y = 0;
	current_block.rotation = 0;
}

void bl_move_left(void) {
	if (current_block.x > 0)
		current_block.x--;
}

void bl_move_right(void) {
	if (current_block.x < ((BOARD_WIDTH)-current_block.sizeX))
		current_block.x++;
}

void bl_move_down(block_t * block) {
	if (!block) {
		return;
	}

	if (block->y <= ((BOARD_HEIGHT-1)-block->sizeY)) {
		block->y++;
	}
}

void bl_rotate_right(void) {
	if (current_block.type == o_block) { // No rotation needed
		return;
	}

	if (current_block.rotation == 270) {
		current_block.rotation = 0;
	}
	else {
		current_block.rotation += 90;
	}

	bl_set_block_type(current_block.type);
}

void bl_rotate_left(void) {
	if (current_block.type == o_block) { // No rotation needed
		return;
	}

	if (current_block.rotation == 0) {
		current_block.rotation = 270;
	}
	else {
		current_block.rotation -= 90;
	}

	bl_set_block_type(current_block.type);
}

void bl_reflect(void) {
	block_t copy;
	int x, y;

	if (current_block.type == o_block || current_block.type == i_block) { // No reflection needed
		return;
	}

	memcpy(&copy, &current_block, sizeof(copy));

	for (y = 0; y < current_block.sizeY; y++) {
		for (x = 0; x < current_block.sizeX; x++) {
			current_block.tab[(current_block.sizeX-1)-x][y] = copy.tab[x][y];
		}
	}
	bl_set_max_sizes(&current_block);
}

void bl_draw(void) {
	int x, y;
	for (y = 0; y < current_block.sizeY; y++) {
		for (x = 0; x < current_block.sizeX; x++) {
			if (current_block.tab[x][y] == 1) {
				mvprintw(current_block.y+y, current_block.x+x+5, "*");
			}
		}
	}
}