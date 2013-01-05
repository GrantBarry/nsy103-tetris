
#include "block.h"

void bl_set_i(void) {
	int x, y;
	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			current_block.tab[x][y] = BLOCK_I[y][x];
		}
	}
	current_block.sizeX = 1;
	current_block.sizeY = 4;
	current_block.type = i_block;
	current_block.rotation = 0;
}

void bl_set_l(void) {
	int x, y;
	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			current_block.tab[x][y] = BLOCK_L[y][x];
		}
	}
	current_block.sizeX = 2;
	current_block.sizeY = 3;
	current_block.type = l_block;
	current_block.rotation = 0;
}

void bl_set_o(void) {
	int x, y;
	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			current_block.tab[x][y] = BLOCK_O[y][x];
		}
	}
	current_block.sizeX = 2;
	current_block.sizeY = 2;
	current_block.type = o_block;
	current_block.rotation = 0;
}

void bl_set_s(void) {
	int x, y;
	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			current_block.tab[x][y] = BLOCK_S[y][x];
		}
	}
	current_block.sizeX = 3;
	current_block.sizeY = 2;
	current_block.type = s_block;
	current_block.rotation = 0;
}

void bl_set_t(void) {
	int x, y;
	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			current_block.tab[x][y] = BLOCK_T[y][x];
		}
	}
	current_block.sizeX = 3;
	current_block.sizeY = 2;
	current_block.type = t_block;
	current_block.rotation = 0;
}

void bl_set_block_type(enum block_type t) {
	switch (t) {
		case i_block:
			bl_set_i();
			break;
		case l_block:
			bl_set_l();
			break;
		case o_block:
			bl_set_o();
			break;
		case s_block:
			bl_set_s();
			break;
		case t_block:
			bl_set_t();
			break;
		}
}

// Moves the actual block up to the top-left of the block array (removes spaces before the block)
void bl_clean(void) {
	int x, y, startX, startY;
	block_t copy;
	
	startX = 0;	
	for (x = 0; x < BLOCK_WIDTH; x++) {
		for (y = 0; y < BLOCK_HEIGHT; y++) {		
			if (current_block.tab[x][y] != 0) {
				startX = x;
				break;
			}
		}
		if (startX != 0) {
			break;
		}
	}
	
	startY = 0;	
	for (y = 0; y < BLOCK_HEIGHT; y++) {		
		for (x = 0; x < BLOCK_WIDTH; x++) {
			if (current_block.tab[x][y] != 0) {
				startY = y;
				break;
			}
		}
		if (startY != 0) {
			break;
		}
	}
	
	memcpy(&copy, &current_block, sizeof(copy));
	memset(current_block.tab, '\0', sizeof(current_block.tab));
	for (y = 0; y < current_block.sizeY; y++) {
		for (x = 0; x < current_block.sizeX; x++) {
			current_block.tab[x][y] = copy.tab[x+startX][y+startY];
		}
	}
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
	if (current_block.x < ((BOARD_WIDTH-1)-current_block.sizeX))
		current_block.x++;
}

void bl_move_down(void) {
	if (current_block.y <= ((BOARD_HEIGHT-1)-current_block.sizeY)) {
		current_block.y++;
	}
}

void bl_rotate_right(void) {
	block_t copy;
	int x, y;
	
	if (current_block.type == o_block) { // No rotation needed
		return;
	}

	memcpy(&copy, &current_block, sizeof(copy));
	/*
	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			copy.tab[x][y] = block.tab[x][y];
		}
	}*/
	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			current_block.tab[y][BLOCK_HEIGHT-x] = copy.tab[x][y];
		}
	}
	
	/*
	x = block.sizeX;
	block.sizeX = block.sizeY;
	block.sizeY = x;
	*/
	swap(current_block.sizeX, current_block.sizeY);
	
	// Eat the empty lines / move the block up to the top-left
	bl_clean();

	current_block.rotation = (current_block.rotation+270)%360;
}

void bl_rotate_left(void) {
	block_t copy;
	int x, y;

	if (current_block.type == o_block) { // No rotation needed
		return;
	}
	
	memcpy(&copy, &current_block, sizeof(copy));
	/*
	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			copy.tab[x][y] = block.tab[x][y];
		}
	}*/
	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			current_block.tab[y][x] = copy.tab[x][y];
		}
	}

	/*
	x = block.sizeX;
	block.sizeX = block.sizeY;
	block.sizeY = x;
	*/
	swap(current_block.sizeX, current_block.sizeY);
	
	// Eat the empty lines / move the block up to the top-left
	bl_clean();

	current_block.rotation = (current_block.rotation+90)%360;
}

void bl_reflect(void) {
	block_t copy;
	int x, y;

	if (current_block.type == o_block || current_block.type == i_block) { // No reflection needed
		return;
	}

	memcpy(&copy, &current_block, sizeof(copy));
	/*
	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			copy.tab[x][y] = block.tab[x][y];
		}
	}*/
	for (y = 0; y < BLOCK_HEIGHT; y++) {
		for (x = 0; x < BLOCK_WIDTH; x++) {
			current_block.tab[BLOCK_WIDTH-x][y] = copy.tab[x][y];
		}
	}
	
	// Eat the empty lines / move the block up to the top-left
	bl_clean();
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

