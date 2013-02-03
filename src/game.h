#ifndef __GAME_H__
#define __GAME_H__

#include "defs.h"
#include "board.h"
#include "net.h"
#include "ai.h"

void g_new_game(void);
void g_cycle(int kb_input);
void g_manage_kb(int kb_input);
void g_manage_server_commands(void);
void g_draw(void);
void g_game_over(void);
void g_log_result(void);
void g_move_block_to_best_location(block_t *block);

#endif