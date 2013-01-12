
#include "game.h"


void g_new_game(void) {
	points = 0;

	bl_reset(&current_block);

	// If not connected, generate a block
	if (net_connected == 0) {
		bl_set_block_type(&current_block, i_block);
	}
	else {
		bl_set_block_type(&current_block, i_block); // TEMP !!!!!!!
		ai_suggest_best_block_location();
	}
}

void g_cycle(int kb_input) {
	int x, y;

	if (net_connected == 0) {
		g_manage_kb(kb_input);
	}
	else {
//		ai_suggest_best_block_location();

		// Move the block to the best location
		ai_move_block_to_best_location(&current_block);
	}
	
	bl_move_down(&current_block);

	if (b_does_collide(&current_block) == 1) {
		for (y = 0; y < current_block.sizeY; y++) {
			for (x = 0; x < current_block.sizeX; x++) {
				if (current_block.tab[x][y] == 1) {
					board[x+current_block.x][y+current_block.y] = 1;
				}
			}
		}

		bl_reset(&current_block);
		bl_set_block_type(&current_block, (current_block.type+1)%5);
		if (net_connected == 1) {
			// Get a new block and calculate the best location
			ai_suggest_best_block_location();
		}
	}

	points += b_remove_lines();
}

void g_manage_kb(int kb_input) {
	switch (kb_input) {
		case 'q':
		case 'Q':
			done = 1;
			return;
		case 'a':
		case 'A':
			bl_rotate_left(&current_block);
			return;
		case 'z':
		case 'Z':
			bl_rotate_right(&current_block);
			return;
		case 'r':
		case 'R':
			bl_reflect(&current_block);
			return;
		case KEY_LEFT:
			bl_move_left(&current_block);
			return;
		case KEY_RIGHT:
			bl_move_right(&current_block);
			return;
		case KEY_DOWN:
			b_drop_block(&current_block);
			return;
		default:
			break;
	}
}

void g_draw(void) {
	clear();
	b_draw_board();
	bl_draw(&current_block);
	mvprintw(2, BOARD_DRAW_OFFSET + BOARD_WIDTH + 2, "Points: %d", points);
	if (net_connected == 1) {
		// Draw the ai block in color
		start_color();
		init_pair(1, COLOR_BLUE, COLOR_BLACK);
		attron(COLOR_PAIR(1));
		bl_draw(&ai_block);
		attroff(COLOR_PAIR(1));
	}
	usleep(50000);
	refresh();
}