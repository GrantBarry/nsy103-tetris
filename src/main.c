/*
Authors: Grant Barry & Eric
Date: 1012/2013
Description: Tetris client for CNAM course NSY103 (CNAM, Nord).
*/
#include "main.h"

int main(int argc, char *argv[]) {
	int kb_input;

	strcpy(game_server_ip, DEFAULT_SERVER_IP);
	game_server_port = DEFAULT_SERVER_PORT;

	// ai_height_weight = 3.0;
	// ai_line_weight = -2.0;
	// ai_empty_blocks_weight = 5.0;
	ai_height_weight = 0.1;
	ai_line_weight = 2.0;
	ai_empty_blocks_weight = 0.2;

	auto_mode = 1;

	if (argc > 1) {
		// Manage commandline arguments
		m_manageArgs(argc, argv);
	}

	m_init();

	g_new_game();

	while (done == 0) {
		g_draw();
		kb_input = getch();
		g_cycle(kb_input);
	}

	m_deinit();

	return EXIT_SUCCESS;
}

void error(char *message) {
	m_deinit();
	printf(message);
	perror(message);
	exit(EXIT_FAILURE);
}

void m_manageArgs(int argc, char *argv[]) {
	int option;

	while ((option = getopt(argc, argv, "dmh:l:e:s:p:")) != -1) {
		switch (option) {
		case 'd' :
			debug = 1;
			printf("[m_manageArgs] debug set to %d\n", debug);
			break;
		case 'm' :
			auto_mode = 0;
			printf("[m_manageArgs] auto_mode set to %d\n", auto_mode);
			break;
		case 'h' :
			ai_height_weight = atof(optarg);
			printf("[m_manageArgs] ai_height_weight set to %f\n", ai_height_weight);
			break;
		case 'l' :
			ai_line_weight = atof(optarg);
			printf("[m_manageArgs] ai_line_weight set to %f\n", ai_line_weight);
			break;
		case 'e' :
			ai_empty_blocks_weight = atof(optarg);
			printf("[m_manageArgs] ai_empty_blocks_weight set to %f\n", ai_empty_blocks_weight);
			break;
		case 's' :
			snprintf(game_server_ip, IP_STRING_SIZE, "%s", optarg);
			printf("[m_manageArgs] game_server_ip set to %s\n", game_server_ip);
			break;
		case 'p' :
			game_server_port = atoi(optarg);
			printf("[m_manageArgs] game_server_port set to %d\n", game_server_port);
			break;
		default:
			m_printHelp();
			exit(EXIT_SUCCESS);
		}
	}
}

void m_printHelp(void) {
	printf("Tetris %s for CNAM course NSY103, 2012/2013\n\n", VERSION);

	printf("tetris_client [options]\n\n");

	printf("Here is a full list of options:\n");
	printf(" -h VALUE		Sets the AI height weight\n");
	printf(" -l VALUE		Sets the AI line weight\n");
	printf(" -e VALUE		Sets the AI empty block weight\n");

	printf(" -s SERVER IP 	Tries to connect to the IP specified\n");
	printf(" -p PORT        Sets the port to use during network connections\n\n");

	printf(" -d             Display debug information\n");
	printf(" -m             Sets the game to manual mode (user can play Tetris)\n\n");
	printf("\n\n");
	printf("Example : tetris_client -s 127.0.0.1 -p 5000\t\tThe client will try to connect to a localhost on port 5000\n");
}

void m_init(void) {
	done = 0;

	// Initialize ncurses lib (libncurses5-dev)
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	cbreak();

	if (auto_mode == 1) {
		net_init();
		net_connect(game_server_ip, game_server_port);
		nodelay(stdscr, TRUE); // Do not wait for kb_input
	}
}

void m_deinit(void) {
	net_disconnect();
	endwin();
}