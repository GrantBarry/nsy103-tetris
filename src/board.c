
#include "board.h"

void b_draw_board(void) {
	int x, y;
	for (y = 0; y < BOARD_HEIGHT; y++) {
		mvprintw(y, 0, "%d", y);
		for (x = 0; x < BOARD_WIDTH; x++) {
			if (board[x][y] > 0) {
				mvprintw(y, x+BOARD_DRAW_OFFSET, "#"); // Print a solid block to the screen
			}
		}
	}
}

// Returns 1 if the block collides with the board
unsigned int b_does_collide(block_t * block) {
	int x, y;

	if (block->y >= BOARD_HEIGHT-block->sizeY) {
		return 1;
	}
	
	// Check for collisions
	for (y = block->sizeY-1; y >= 0; y--) {
		for (x = 0; x < block->sizeX; x++) {
			if ((block->tab[x][y] > 0) && (board[block->x + x][block->y + y + 1] > 0)) {
				return 1;
			}
		}
	}
	
	return 0;
}

// Returns the number of complete lines on the board
int b_get_num_lines(void) {
	int x, y, result = 0;
	
	for (y = 0; y < BOARD_HEIGHT; y++) {
		if (b_is_full_line(y) == 1) {
			result++;
		}
	}
	
	return result;
}

int b_get_num_empty_blocks(void) {
	int x, y, result = 0;
	int skyline[BOARD_WIDTH];

	// Calculate the skyline for this cycle
	for (x = 0; x < BOARD_WIDTH; x++) {
		y = 0;
		while (board[x][y] == 0 && y < BOARD_HEIGHT) {
			y++;
		}
		skyline[x] = y;
	}
	
	for (x = 0; x < BOARD_WIDTH; x++) {
		for (y = skyline[x]; y < BOARD_HEIGHT; y++) {
			if (board[x][y] == 0) {
				result++;
			}
		}
	}
	
	return result;
}

// Sets the block coordinates to the lowest position (on the board)
void b_drop_block(block_t * block) {
	unsigned int collision = 0;
	block_t copy;

	memcpy(&copy, block, sizeof(copy));
	
	collision = b_does_collide(&copy);
	
	while (collision == 0) {
		bl_move_down(&copy);
		collision = b_does_collide(&copy);
	}

	block->y = copy.y-1;
}

// Remove full lines
unsigned int b_remove_lines(void) {
	int y;
	unsigned int num_lines_removed = 0;
	for (y = BOARD_HEIGHT-1; y >= 0; y--) {
		if (b_is_full_line(y) == 1) {
			b_remove_line(y);
			y++;
			num_lines_removed++;
		}
	}
	return num_lines_removed;
}

void b_remove_line(int line) {
	int x, y;
	
	if (line > BOARD_HEIGHT) {
		return;
	}
	
	if (line > 0) {
		for (y = line; y > 0; y--) {
			for (x = 0; x < BOARD_WIDTH; x++) {
				board[x][y] = board[x][y-1];
			}		
		}		
	}
	// Set the first line (y = 0) to 0
	for (x = 0; x < BOARD_WIDTH; x++) {
		board[x][0] = 0;
	}
}

int b_is_full_line(int line) {
	int x, y, i;
	for (y = 0; y < BOARD_HEIGHT; y++) {
		i = 0;
		for (x = 0; x < BOARD_WIDTH; x++) {
			i += board[x][y];
		}
		if (i >= BOARD_WIDTH) {
			return 1;
		}
	}
	return 0;
}

void b_insert_line(int data[BOARD_WIDTH]) {
	int x, y;
	for (y = 0; y < BOARD_HEIGHT-1; y++) {
		for (x = 0; x < BOARD_WIDTH; x++) {
			board[x][y] = board[x][y+1];
		}
	}

	for (x = 0; x < BOARD_WIDTH; x++) {
		board[x][BOARD_HEIGHT-1] = data[x];
	}
}