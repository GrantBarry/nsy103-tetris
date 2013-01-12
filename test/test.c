#define BOARD_HEIGHT 25
#define BOARD_WIDTH 12


#include <stdio.h>


void swap(int * i, int * j) {
	int temp;
	temp = *i;
	*i = *j;
	*j = temp;
}

int test1() {
	int i, j;
	i = 4;
	j = 5;
	printf("\nTest1\n\n");
	printf("i is set to %d\n", i);
	printf("j is set to %d\n", j);
	swap(&i, &j);
	if (i == 5 && j == 4) {
		printf("SUCCESS\n");
		return 0;
	}
	else {
		return 1;
	}
}

int test2() {
	int skyline[BOARD_WIDTH];
	int board[BOARD_WIDTH][BOARD_HEIGHT];
	int x, y;

	for (x = 0; x < BOARD_WIDTH; x++) {
		for (y = 0; y < BOARD_HEIGHT; y++) {
			board[x][y] = 0;
		}
	}

	board[0][5] = 1;
	board[1][9] = 1;
	board[2][16] = 1;
	board[5][5] = 1;
	board[8][2] = 1;
	board[9][15] = 1;

	// for (x = 0; x < BOARD_WIDTH; x++) {
	// 	board[x][x] = 1;
	// }

	for (x = 0; x < BOARD_WIDTH; x++) {
		y = 0;
		while (board[x][y] == 0 && y < BOARD_HEIGHT-1) {
			y++;
		}
		skyline[x] = y;
	}
 
	for (x = 0; x < BOARD_WIDTH; x++) {
		printf("%d\n", skyline[x]);
	}

	return 0;
}

int main(void) {
	int result = 0;
	result += test1();

	result += test2();
	return result;
}