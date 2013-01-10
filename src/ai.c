 #include "ai.h"

//void ai_suggestBestBlockLocation(int board[BOARD_WIDTH][BOARD_HEIGHT], block_t block, float heightWeight, float solidLineWeight, float emptyBlockWeight) {
void ai_suggest_best_block_location(void) {
	int blockIndex, blockReflectionIndex, x, y, i;
	float numHeight, numSolidLines, numEmptyBlocks, numPoints;
	float bestResult = 0.0;
	float result = 0.0;
	int boardCopy[BOARD_WIDTH][BOARD_HEIGHT];
	int skyline[BOARD_WIDTH];
	block_t blockCopy[4][2]; // A block copy for each rotation (0°, 90°, 180° and 270°) and it's reflection
	
	// 0°
	memcpy(&blockCopy[0][0], &current_block, sizeof(blockCopy[0][0]));

	// 90°
	memcpy(&blockCopy[1][0], &current_block, sizeof(blockCopy[1][0]));
	bl_rotate_left(&blockCopy[1][0]);
	
	// 180°
	memcpy(&blockCopy[2][0], &blockCopy[1][0], sizeof(blockCopy[2][0]));
	bl_rotate_left(&blockCopy[2][0]);
	
	// 270°
	memcpy(&blockCopy[3][0], &current_block, sizeof(blockCopy[3][0]));
	bl_rotate_right(&blockCopy[3][0]);

	// Reflections
	for (blockIndex = 0; blockIndex <= 3; blockIndex++) {
		memcpy(&blockCopy[blockIndex][1], &blockCopy[blockIndex][0], sizeof(blockCopy[blockIndex][1]));
		bl_reflect(&blockCopy[blockIndex][1]);		
	}

	// Save a copy of the game board
	memcpy(&boardCopy, &board, sizeof(boardCopy));

	for (blockReflectionIndex = 0; blockReflectionIndex < 2; blockReflectionIndex++) {	
		for (blockIndex = 0; blockIndex < 4; blockIndex++) {
			// Move the block from left to right and find the best fit based on the given weights
			for (i = 0; i < (BOARD_WIDTH)-blockCopy[blockIndex][blockReflectionIndex].sizeX; i++) {
				
				blockCopy[blockIndex][blockReflectionIndex].x = i;
				b_drop_block(&blockCopy[blockIndex][blockReflectionIndex]);
				bl_draw(&blockCopy[blockIndex][blockReflectionIndex]);
				
				// Calculate the height impact
				for (x = 0; x < BOARD_WIDTH; x++) {
					y = 0;
					while (board[x][y] == 0 && y < BOARD_HEIGHT-1) {
						y++;
					}
					skyline[x] = y;
				}
				numHeight = 0.0;
				for (x = 0; x < BOARD_WIDTH; x++) {
					numHeight += (float)skyline[x];
				}

				// Get the number of solid lines
				numSolidLines = (float)b_get_num_lines();
				
				// Get the number of empty blocks
				numEmptyBlocks = (float)b_get_num_empty_blocks();

				// The number of points for moving the block
				
				// Neuron function
				result = (numHeight*ai_height_weight) + (numSolidLines*ai_line_weight) + (numEmptyBlocks*ai_empty_blocks_weight);

				if (result >= bestResult) {
					// We have a better location, so overwrite the block with the blockCopy[blockIndex]
					memcpy(&ai_block, &blockCopy[blockIndex][blockReflectionIndex], sizeof(ai_block));
					bestResult = result;
				}

				// Now restore the board
				memcpy(&board, &boardCopy, sizeof(board));
			}
		}
	}
}

void ai_move_block_to_best_location(block_t * block) {
	if (!block) {
		return;
	}

	// Manage coordinates first
	if (block->x < ai_block.x) {
		bl_move_right(block);
		return;
	}
	if (block->x > ai_block.x) {
		bl_move_left(block);
		return;
	}

	// Manage rotation
	if (block->rotation < ai_block.rotation) {
		bl_rotate_left(block);
		return;
	}

	if (block->rotation > ai_block.rotation) {
		bl_rotate_right(block);
		return;
	}

	b_drop_block(block);
}