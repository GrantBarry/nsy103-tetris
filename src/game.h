#ifndef __GAME_H__
#define __GAME_H__

#include "defs.h"
#include "board.h"
#include "net.h"
#include "ai.h"

char game_server_ip[IP_STRING_SIZE];
int game_server_port;
unsigned int points;
unsigned int debug;

void g_new_game(void);
void g_cycle(int kb_input);
void g_manage_kb(int kb_input);
void g_draw(void);
void g_game_over(void);
void g_log_result(void);

#endif