 #include "ai.h"

//void ai_suggestBestBlockLocation(int board[BOARD_WIDTH][BOARD_HEIGHT], block_t block, float heightWeight, float solidLineWeight, float emptyBlockWeight) {
void ai_suggest_best_block_location(int board[BOARD_WIDTH][BOARD_HEIGHT]) {
	int blockIndex, blockReflectionIndex, x, y, i;
	float numHeight, numSolidLines, numEmptyBlocks;
	float bestResult = 0.0;
	float result;
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

	for (blockReflectionIndex = 0; blockReflectionIndex < 2; blockReflectionIndex++) {	
		for (blockIndex = 0; blockIndex <= 3; blockIndex++) {
			// Move the block from left to right and find the best fit based on the given weights
			for (x = 0; x < (BOARD_WIDTH-1)-blockCopy[blockIndex][blockReflectionIndex].sizeX; x++) {
				// Save a copy of the game board
				memcpy(&boardCopy, &board, sizeof(boardCopy));
				b_drop_block(&blockCopy[blockIndex][blockReflectionIndex]);
				bl_draw(&blockCopy[blockIndex][blockReflectionIndex]);
				
				// Calculate the height impact
				numHeight = 0.0;
				for (x = 0; x < BOARD_WIDTH; x++) {
					for (y = BOARD_HEIGHT-1; y >= 0; y--) {
						if (board[x][y] == 1) {
							//skyline[x] = y;
						} 
					}
				}
				for (i = 0; i < BOARD_WIDTH; i++) {
					numHeight += (float)BOARD_HEIGHT-(skyline[i]+1);
				}
				
				// Get the number of solid lines
				//numSolidLines = (float)b_get_num_lines(boardCopy);
				
				// Get the number of empty blocks
				//numEmptyBlocks = (float)b_get_num_empty_blocks(boardCopy);
				
				// Neuron function
				result = (numHeight*ai_height_weight) + (numSolidLines*ai_line_weight) + (numEmptyBlocks*ai_empty_blocks_weight);

				// The number of points for moving the block
				
				if (result > bestResult) {// We have a better location, so overwrite the block with the blockCopy[blockIndex]
					memcpy(&ai_block, &blockCopy[blockIndex][blockReflectionIndex], sizeof(ai_block));
					bestResult = result;
				}
//				ai_block.x = 0;
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
	else if (block->x > ai_block.x) {
		bl_move_left(block);
		return;
	}

	// Manage rotation
	if (block->rotation < ai_block.rotation) {
		bl_rotate_left(block);
		return;
	}
}