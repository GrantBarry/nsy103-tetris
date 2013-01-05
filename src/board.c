
#include "board.h"

void b_draw_board(void) {
	int x, y;
	for (y = 0; y < BOARD_HEIGHT; y++) {
		mvprintw(y, 0, "%d", y);
		for (x = 0; x < BOARD_WIDTH; x++) {
			if (board[x][y] > 0) {
				mvprintw(y, x+5, "#"); // Print a solid block to the screen
			}
		}
	}
}

// Returns 1 if the block collides with the board
unsigned int b_does_collide(void) {
	int x, y;

	if (current_block.y >= ((BOARD_HEIGHT)-current_block.sizeY)) {
		return 1;
	}
	
	// Check for collisions
	for (y = 0; y < current_block.sizeY; y++) {
		for (x = 0; x < current_block.sizeX; x++) {
			if ((current_block.tab[x][y] > 0) && (board[current_block.x + x][current_block.y + y + 1] > 0)) {
				return 1;
			}
		}
	}
	
	return 0;
}

void b_getSkyline(int board[BOARD_WIDTH][BOARD_HEIGHT], int * skyline) {
	int x, y;
	for (x = 0; x < BOARD_WIDTH; x++) {
		y = 0;
		while (board[x][y] == 0 && y < BOARD_HEIGHT-1) {
			y++;
		}
		skyline[x] = y;
	}	
}

// Returns the number of complete lines on the board
int b_getNumLines(int board[BOARD_WIDTH][BOARD_HEIGHT]) {
	int x, y, lineCount, result = 0;
	
	for (y = 0; y < BOARD_HEIGHT; y++) {
		lineCount = 0;
		for (x = 0; x < BOARD_WIDTH; x++) {
			if (board[x][y] > 0) {
				lineCount++;
			}
		}
		if (lineCount >= BOARD_WIDTH) {
			result++;
		}
	}
	
	return result;
}

// Returns the number of empty blocks (holes) below the skyline
int b_getNumBlocks(int board[BOARD_WIDTH][BOARD_HEIGHT]) {
	int x, y, result = 0;
	int skyline[BOARD_WIDTH];
	
	// Calculate the skyline for this cycle
	b_getSkyline(board, &skyline);
	
	for (x = 0; x < BOARD_WIDTH; x++) {
		for (y = skyline[x]+1; y < BOARD_HEIGHT; y++) {
			if (board[x][y] == 0) {
				result++;
			}
		}
	}
	
	return result;
}

// Sets the block coordinates to the lowest position (on the board)
void b_drop_block(void) {
	unsigned int collision = 0;
	
	collision = b_does_collide();
	
	while (collision == 0) {
		bl_move_down();
		collision = b_does_collide();
	}
}

