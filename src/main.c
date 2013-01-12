




#include "main.h"

int main(int argc, char *argv[]) {
	int kb_input;

	// Set our server IP address to 'none'
	strcpy(game_server_ip, DEFAULT_SERVER_IP);

	ai_height_weight = 2.0;
	ai_line_weight = 1.0;
	ai_empty_blocks_weight = 4.0;

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
		usleep(250);
	}

	m_deinit();
	
	return EXIT_SUCCESS;

}

void error(char * message) {
	perror(message);
	exit(EXIT_FAILURE);
}

void swap(int * i, int * j) {
	int temp;
	temp = *i;
	*i = *j;
	*j = temp;
}

void m_manageArgs(int argc, char *argv[]) {
	int option;

    while ((option = getopt(argc, argv,"zbh:l:e:s:p:")) != -1) {
        switch (option) {
        	case 'z' :
        		debug = 1;
        		printf("[m_manageArgs] debug set to %d\n", debug);
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
	
	printf("main [options]\n\n");
	
	printf("Here is a full list of options:\n");
	printf(" -h VALUE		Sets the AI height weight\n");
	printf(" -l VALUE		Sets the AI line weight\n");
	printf(" -e VALUE		Sets the AI empty block weight\n");
	
	printf(" -s SERVER IP 	Tries to connect to the IP specified\n");
	printf(" -p PORT        Sets the port to use during network connections\n\n");
	printf("\n\n");
}

void m_init(void) {
	done = 0;

	// Initliaze ncurses lib (libncurses5-dev)
	initscr();
	noecho();
	keypad(stdscr, TRUE);
	//nodelay(stdscr,TRUE);
	cbreak();

	if (strcmp(game_server_ip, DEFAULT_SERVER_IP) != 0) {
		net_init();
		net_connect();
		nodelay(stdscr,TRUE); // Do not wait for kb_input
	}
}

void m_deinit(void) {
	net_disconnect();

	endwin();
}