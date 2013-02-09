#include "ai.h"

//void ai_suggestBestBlockLocation(int board[BOARD_WIDTH][BOARD_HEIGHT], block_t block, float heightWeight, float solidLineWeight, float emptyBlockWeight) {
void ai_suggest_best_block_location(void) {
	int blockIndex, blockReflectionIndex, x, y, i;
	float numHeight, numSolidLines, numEmptyBlocks, numPoints;
	float bestResult = 1000000.0;
	float result = 0.0;
	int boardCopy[BOARD_WIDTH][BOARD_HEIGHT];
	int skyline[BOARD_WIDTH];
	block_t blockCopy[4][2]; // A block copy for each rotation (0°, 90°, 180° and 270°) and it's reflection
	block_t testBlock;

	bl_reset(&ai_block);

	// 0°
	memcpy(&blockCopy[0][0], &current_block, sizeof(blockCopy[0][0]));

	// 90°
	memcpy(&blockCopy[1][0], &current_block, sizeof(blockCopy[1][0]));
	bl_rotate_anti_clockwise(&blockCopy[1][0]);

	// 180°
	memcpy(&blockCopy[2][0], &blockCopy[1][0], sizeof(blockCopy[2][0]));
	bl_rotate_anti_clockwise(&blockCopy[2][0]);

	// 270°
	memcpy(&blockCopy[3][0], &current_block, sizeof(blockCopy[3][0]));
	bl_rotate_clockwise(&blockCopy[3][0]);

	// Reflections
	for (blockIndex = 0; blockIndex < 4; blockIndex++) {
		memcpy(&blockCopy[blockIndex][1], &blockCopy[blockIndex][0], sizeof(blockCopy[blockIndex][1]));
		bl_reflect(&blockCopy[blockIndex][1]);
	}

	// Save a copy of the game board
	memcpy(&boardCopy, &board, sizeof(int)*BOARD_WIDTH * BOARD_HEIGHT);

	for (blockReflectionIndex = 0; blockReflectionIndex < 2; blockReflectionIndex++) {
		for (blockIndex = 0; blockIndex < 4; blockIndex++) {
			// Move the block from left to right and find the best fit based on the given weights
			for (i = 0; i <= (BOARD_WIDTH - blockCopy[blockIndex][blockReflectionIndex].sizeX); i++) {

				memcpy(&testBlock, &blockCopy[blockIndex][blockReflectionIndex], sizeof(testBlock));

				testBlock.x = i;
				b_drop_block(&testBlock);
				testBlock.y++;
				for (y = 0; y < testBlock.sizeY; y++) {
					for (x = 0; x < testBlock.sizeX; x++) {
						if (testBlock.tab[x][y] == 1) {
							board[x+testBlock.x][y+testBlock.y] = 1;
						}
					}
				}

				// Calculate the height impact
				for (x = 0; x < BOARD_WIDTH; x++) {
					y = 0;
					while (board[x][y] == 0 && y < BOARD_HEIGHT) {
						y++;
					}
					skyline[x] = BOARD_HEIGHT - y;
				}
				numHeight = 0.0;
				for (x = 0; x < BOARD_WIDTH; x++) {
					numHeight += (float)skyline[x] * skyline[x];
				}

				// Get the number of solid lines
				numSolidLines = (float)b_get_num_lines();

				// Get the number of empty blocks
				numEmptyBlocks = (float)b_get_num_empty_blocks();

				// The number of points for moving the block
				// ........... TODO .......

				// Neuron function
				result = (numHeight * ai_height_weight) + (numSolidLines * -1 * ai_line_weight) + (numEmptyBlocks * ai_empty_blocks_weight);

				if (debug == 1) {
					clear();
					b_draw_board();
					bl_draw(&testBlock);
					start_color();
					init_pair(1, COLOR_BLUE, COLOR_BLACK);
					attron(COLOR_PAIR(1));
					bl_draw(&ai_block);
					attroff(COLOR_PAIR(1));

					mvprintw(17, 19, "%d + %d = %d [%d]", testBlock.x, testBlock.sizeX, testBlock.x + testBlock.sizeX, BOARD_WIDTH);
					mvprintw(18, 19, "%d x %d", testBlock.sizeX, testBlock.sizeY);
					mvprintw(19, 19, "%f (height = %f), (solid = %f), (empty = %f)", result, numHeight, numSolidLines, numEmptyBlocks);
					mvprintw(20, 19, "ai_block.rotation set to %d", ai_block.rotation);
					if (ai_block.reflected == 1) {
						mvprintw(21, 19, "REFLECTED");
					}
					for (x = 0; x < BOARD_WIDTH; x++) {
						mvprintw(x, 30, "%d", skyline[x]);
					}
					refresh();
					usleep(100000);
				}

				// Now restore the board
				memcpy(&board, &boardCopy, sizeof(int)*BOARD_WIDTH * BOARD_HEIGHT);

				if (result < bestResult) {
					// We have a better location, so overwrite the block with the blockCopy[blockIndex]
					memcpy(&ai_block, &testBlock, sizeof(ai_block));
					bestResult = result;
				}
			}
		}
	}
}

//void ai_move_block_to_best_location(block_t * block) {
// if (!block) {
// 	return;
// }

// // Manage rotation
// if (ai_block.rotation > block->rotation) {
// 	bl_rotate_anti_clockwise(block);
// 	net_send_rotate_right();
// 	return;
// }

// if (ai_block.rotation == 270 && ai_block.rotation != block->rotation) {
// 	bl_rotate_clockwise(block);
// 	net_send_rotate_left();
// 	return;
// }

// // Manage coordinates
// if (block->x < ai_block.x) {
// 	bl_move_right(block);
// 	net_send_right();
// 	return;
// }
// if (block->x > ai_block.x) {
// 	bl_move_left(block);
// 	net_send_left();
// 	return;
// }

// // And relfection
// if (ai_block.reflected != block->reflected) {
// 	bl_reflect(block);
// 	net_send_invert();
// 	return;
// }

// b_drop_block(block);
// net_send_full_down();
//}