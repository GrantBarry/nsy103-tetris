
#include "game.h"


void g_new_game(void) {
	bl_reset();

	// If not connected, generate a block
	if (net_connected == 0) {
		bl_set_block_type(l_block);
	}
}

void g_cycle(int kb_input) {
	int x, y;

	g_manage_kb(kb_input);
	bl_move_down();

	if (b_does_collide() == 1) {
		for (y = 0; y < current_block.sizeY; y++) {
			for (x = 0; x < current_block.sizeX; x++) {
				if (current_block.tab[x][y] == 1) {
					board[x+current_block.x][y+current_block.y] = 1;
				}
			}
		}

		bl_reset();
		bl_set_block_type((current_block.type+1)%5);
	}
}

void g_manage_kb(int kb_input) {
	switch (kb_input) {
		case 'q':
		case 'Q':
			done = 1;
			return;
		case 'a':
		case 'A':
			bl_rotate_left();
			return;
		case 'z':
		case 'Z':
			bl_rotate_right();
			return;
		case KEY_LEFT:
			bl_move_left();
			return;
		case KEY_RIGHT:
			bl_move_right();
			return;
		case KEY_DOWN:
			b_drop_block();
			return;
		default:
			break;
	}
}

void g_draw(void) {
	clear();
	b_draw_board();
	bl_draw();
	refresh();
}