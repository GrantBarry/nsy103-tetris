
#include "game.h"


void g_new_game(void) {
	int currentPiece = 0;
	int nextPiece = 0;	

	points = 0;
	bl_reset(&current_block);

	// If we are in manual mode (auto_mode = 0), generate a block
	if (auto_mode == 0) {
		srand ( time(NULL) );
		bl_set_block_type(&current_block, rand() % 9);
	} else {
		net_send_name("Eric_et_Grant");

		net_send_command("110 READY");
		if (net_current_code == 130 && strcmp("GO", net_current_command) == 0) {
			sscanf(net_current_data, "%d %d", &currentPiece, &nextPiece);
			bl_set_current_block(currentPiece - 1);
			bl_set_next_block(nextPiece - 1);
			ai_suggest_best_block_location();
		}
	}
}

void g_cycle(int kb_input) {
	int x, y;

	if (auto_mode == 1) {
		// Sleep half a second before sending code
		usleep(500000);

		// Move the block to the best location
		g_move_block_to_best_location(&current_block);

		//g_manage_server_commands();
	} else {
		g_manage_kb(kb_input);

	}

	bl_move_down(&current_block);

	if (b_does_collide(&current_block) == 1) {
		if (current_block.y <= 1) {
			g_game_over();
			return;
		}
		for (y = 0; y < current_block.sizeY; y++) {
			for (x = 0; x < current_block.sizeX; x++) {
				if (current_block.tab[x][y] == 1) {
					board[x+current_block.x][y+current_block.y] = 1;
				}
			}
		}

		points += b_remove_lines();
	
		if (auto_mode == 0) {
			bl_reset(&current_block);
			bl_set_block_type(&current_block, rand() % 9);
		}
	}

	if (auto_mode == 1) {
		g_manage_server_commands();
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
		bl_rotate_anti_clockwise(&current_block);
		return;
	case 'z':
	case 'Z':
		bl_rotate_clockwise(&current_block);
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

void g_manage_server_commands(void) {
	int currentPiece = 0;
	int nextPiece = 0;
	char buffer[NET_BUFFER_LENGTH];
	int piece, x, y, next_piece, num_new_lines;
	int line[BOARD_WIDTH];

	mvprintw( 26, 2, "enter server commands with %d/%s/%s", net_current_code, net_current_command, net_current_data);
	refresh();
	sleep(3);

	if (net_current_code == 140 && strcmp("END", net_current_command) == 0) {
		g_game_over();
		return;
	} else if (net_current_code == 301 && strcmp("OK", net_current_command) == 0) {
		// if (!net_current_data) {
		// 	return;
		// } else {
			bzero(buffer, sizeof(buffer));
			piece = 0;
			x = 0;
			y = 0;
			next_piece = 0;
			sscanf(net_current_data, "%s %d %d %d %d", buffer, &piece, &x, &y, &next_piece);
			mvprintw( 26, 2, "piece %d at %d,%d next %d, buffer: %s", piece, x, y, next_piece, buffer);
			refresh();
			sleep(3);

			b_set_board_from_string(net_current_data);
			bl_reset(&current_block);
			current_block.x = x;
			current_block.y = y;
			bl_set_current_block(piece - 1);
			bl_set_next_block(next_piece - 1);
			ai_suggest_best_block_location();
		// }
	} else if (net_current_code == 310 && strcmp("OK", net_current_command) == 0) {
		next_piece = 0;
		sscanf(net_current_data, "%d", &next_piece);
		mvprintw( 26, 2, "next piece %d", next_piece);
		refresh();
		sleep(3);

		bl_reset(&current_block);
		bl_push_next_block(next_piece - 1);

		ai_suggest_best_block_location();
	} else if (net_current_code == 320 && strcmp("OK", net_current_command) == 0) {
		num_new_lines = 0;
		bzero(buffer, sizeof(buffer));
		sscanf(net_current_data, "%d %s", &num_new_lines, buffer);
		mvprintw( 26, 2, "num_new_lines %d, buffer: %s", num_new_lines, buffer);
		mvprintw( 27, 2, "net_current_data: %s", net_current_data);
		refresh();
		sleep(3);

		for (x = 0; x < num_new_lines; x++) {
			bzero(&line, sizeof(line));
			for (y = 0; y < BOARD_WIDTH; y++) {
				if (buffer[x*BOARD_WIDTH+y] == '1') {
					line[y] = 1;
				} else {
					line[y] = 0;
				}
			}
			b_insert_line(line);
		}

		ai_suggest_best_block_location();
	} else if (net_current_code == 330 && strcmp("OK", net_current_command) == 0) {
		bzero(buffer, sizeof(buffer));
		next_piece = 0;		
		num_new_lines = 0;
		sscanf(net_current_data, "%d %d %s", &next_piece, &num_new_lines, buffer);
		mvprintw( 26, 2, "next piece %d, num_new_lines %d, buffer: %s", next_piece,num_new_lines,buffer);
		mvprintw( 27, 2, "net_current_data: %s", net_current_data);
		refresh();
		sleep(3);
		bl_reset(&current_block);
		bl_push_next_block(next_piece - 1);

		for (x = 0; x < num_new_lines; x++) {
			bzero(&line, sizeof(line));
			for (y = 0; y < BOARD_WIDTH; y++) {
				if (buffer[x*BOARD_WIDTH+y] == '1') {
					line[y] = 1;
				} else {
					line[y] = 0;
				}
			}
			b_insert_line(line);
		}

		ai_suggest_best_block_location();
	} else if (net_current_code >= 400) {
		// Pour toute commande incorrecte ou incomprise, on va demander une nouvelle copie de la table
		net_send_command("280 DUMP");
		g_manage_server_commands();
	}
}

void g_draw(void) {
	clear();
	b_draw_board();
	bl_draw(&current_block);
	mvprintw(2, BOARD_DRAW_OFFSET + BOARD_WIDTH + 2, "Points: %d", points);

	if (auto_mode == 1) {
		// Draw the ai block in color
		start_color();
		init_pair(1, COLOR_BLUE, COLOR_BLACK);
		attron(COLOR_PAIR(1));
		bl_draw(&ai_block);
		attroff(COLOR_PAIR(1));
	}

	refresh();
}

void g_game_over(void) {
	clear();
	mvprintw( 1, 1, "   _____                      ");
	mvprintw( 2, 1, "  / ____|                     ");
	mvprintw( 3, 1, " | |  __  __ _ _ __ ___   ___ ");
	mvprintw( 4, 1, " | | |_ |/ _` | /_ ` _ \\ / _ \\");
	mvprintw( 5, 1, " | |__| | (_| | | | | | |  __/");
	mvprintw( 6, 1, "  \\_____|\\__,_|_| |_| |_|\\___|");
	mvprintw( 8, 1, "   ____                 ");
	mvprintw( 9, 1, "  / __ \\                ");
	mvprintw(10, 1, " | |  | |_   _____ _ __ ");
	mvprintw(11, 1, " | |  | \\ \\ / / _ \\ |__|");
	mvprintw(12, 1, " | |__| |\\ V /  __/ |   ");
	mvprintw(13, 1, "  \\____/  \\_/ \\___|_|   ");
	refresh();
	done = 1;
	sleep(2);
	g_log_result();
}

void g_log_result(void) {
	FILE *file_pointer;
	file_pointer = fopen("results.log", "a");
	if (file_pointer == NULL) {
		error("unable to open log file");
	}
	fprintf(file_pointer, "ai_height_weight=%f;ai_line_weight=%f;ai_empty_blocks_weight=%f;points=%d\n",
	        ai_height_weight,
	        ai_line_weight,
	        ai_empty_blocks_weight,
	        points
	       );
	fclose(file_pointer);
}

void g_move_block_to_best_location(block_t *block) {
	if (!block) {
		return;
	}

	// Manage rotation
	if (ai_block.rotation > block->rotation && ai_block.rotation != 270) {
		net_send_command("240 ROTATE_R");
		// Server accepted the command
		if (net_current_code >= 300 && net_current_code <= 399) {
			bl_rotate_clockwise(block);
		}
		return;
	}

	if (ai_block.rotation == 270 && ai_block.rotation != block->rotation) {
		net_send_command("250 ROTATE_L");
		// Server accepted the command
		if (net_current_code >= 300 && net_current_code <= 399) {
			bl_rotate_anti_clockwise(block);
		}
		return;
	}

	// Manage coordinates
	if (block->x < ai_block.x) {
		net_send_command("210 RIGHT");
		// Server accepted the command
		if (net_current_code >= 300 && net_current_code <= 399) {
			bl_move_right(block);
		}
		return;
	}
	if (block->x > ai_block.x) {
		net_send_command("200 LEFT");
		// Server accepted the command
		if (net_current_code >= 300 && net_current_code <= 399) {
			bl_move_left(block);
		}
		return;
	}

	// And relfection
	if (ai_block.reflected != block->reflected) {
		net_send_command("260 INVERSE");
		// Server accepted the command
		if (net_current_code >= 300 && net_current_code <= 399) {
			bl_reflect(block);
		}
		return;
	}

	net_send_command("230 FULLDOWN");
	// Server accepted the command
	if (net_current_code >= 300 && net_current_code <= 399) {
		b_drop_block(block);
	}
}