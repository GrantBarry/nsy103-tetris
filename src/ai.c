 #include "ai.h"

//void ai_suggestBestBlockLocation(int board[BOARD_WIDTH][BOARD_HEIGHT], block_t block, float heightWeight, float solidLineWeight, float emptyBlockWeight) {
void ai_suggest_best_block_location(int board[BOARD_WIDTH][BOARD_HEIGHT]) {
	int blockIndex, x, y, i;
	float numHeight, numSolidLines, numEmptyBlocks;
	float bestResult = 0.0;
	float result;
	int boardCopy[BOARD_WIDTH][BOARD_HEIGHT];
	int skyline[BOARD_WIDTH];
	block_t blockCopy[4]; // A block copy for each rotation (0°, 90°, 180° and 270°)
	
	memcpy(&blockCopy[0], &current_block, sizeof(blockCopy[0]));
	
	memcpy(&blockCopy[1], &current_block, sizeof(blockCopy[1]));
	bl_rotate_left(&blockCopy[1]);
	
	memcpy(&blockCopy[2], &blockCopy[1], sizeof(blockCopy[2]));
	bl_rotate_left(&blockCopy[2]);
	
	memcpy(&blockCopy[3], &current_block, sizeof(blockCopy[3]));
	bl_rotate_right(&blockCopy[3]);
	
	for (blockIndex = 0; blockIndex <= 3; blockIndex++) {
		// Move the block from left to right and find the best fit based on the given weights
		for (x = 0; x < (BOARD_WIDTH-1)-blockCopy[blockIndex].sizeX; x++) {
			memcpy(boardCopy, board, sizeof(boardCopy));
			b_drop_block(&blockCopy[blockIndex]);
			//bl_draw(blockCopy[blockIndex], boardCopy);
			
			// Calculate the height impact
			numHeight = 0.0;
			for (x = 0; x < BOARD_WIDTH; x++) {
				y = 0;
				while (board[x][y] == 0 && y < BOARD_HEIGHT-1) {
					y++;
				}
				skyline[x] = y;
			}
			for (i = 0; i < BOARD_WIDTH; i++) {
				numHeight += (float)BOARD_HEIGHT-(skyline[i]+1);
			}
			
			// Get the number of solid lines
			numSolidLines = (float)b_get_num_lines(boardCopy);
			
			// Get the number of empty blocks
			numEmptyBlocks = (float)b_get_num_empty_blocks(boardCopy);
			
			// Neuron function
			result = (numHeight*ai_height_weight) + (numSolidLines*ai_line_weight) + (numEmptyBlocks*ai_empty_blocks_weight);
			
			if (result > bestResult) {// We have a better location, so overwrite the block with the blockCopy[blockIndex]
				//block = bl_copy(blockCopy[blockIndex]);
				memcpy(&current_block, &blockCopy[blockIndex], sizeof(current_block));
				bestResult = result;
			}
		}
	}
}
