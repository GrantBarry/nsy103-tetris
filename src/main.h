#ifndef __MAIN_H__
#define __MAIN_H__


#include "defs.h"

#include "net.h"
#include "block.h"
#include "board.h"
#include "game.h"
#include "ai.h"


void error(char *message);
void swap(int *i, int *j);

void m_manageArgs(int argc, char *argv[]);
void m_printHelp(void);
void m_init(void);
void m_deinit(void);

#endif