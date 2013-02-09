
#include <stdio.h>
#include "../src/defs.h"
#include "../src/board.h"

int test_board_insert_line(void) {
	int board[BOARD_WIDTH][BOARD_HEIGHT];
	int line[BOARD_WIDTH];
	int x;

	bzero(board, sizeof(board));

	for (x = 0; x < BOARD_WIDTH; x++) {
		line[x] = (x+1)%2;
	}
	b_insert_line(line);
	for (x = 0; x < BOARD_WIDTH; x++) {
		line[x] = x%2;
	}
	b_insert_line(line);
	if (
		board[ 0][23] == 1 &&
		board[ 1][23] == 0 &&
		board[ 2][23] == 1 &&
		board[ 3][23] == 0 &&
		board[ 4][23] == 1 &&
		board[ 5][23] == 0 &&
		board[ 6][23] == 1 &&
		board[ 7][23] == 0 &&
		board[ 8][23] == 1 &&
		board[ 9][23] == 0 &&
		board[10][23] == 1 &&
		board[11][23] == 0 &&
		board[ 0][24] == 0 &&
		board[ 1][24] == 1 &&
		board[ 2][24] == 0 &&
		board[ 3][24] == 1 &&
		board[ 4][24] == 0 &&
		board[ 5][24] == 1 &&
		board[ 6][24] == 0 &&
		board[ 7][24] == 1 &&
		board[ 8][24] == 0 &&
		board[ 9][24] == 1 &&
		board[10][24] == 0 &&
		board[11][24] == 1
		) {
		printf("b_insert_line works\n\n");
		return 0;
	} else {
		printf("b_insert_line failed!\n\n");
		return 1;
	}
}

int main(void) {
	int result = 0;

	result += test_board_insert_line();

	return result;
}