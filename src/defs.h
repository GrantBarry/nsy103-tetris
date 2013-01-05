#ifndef __DEFS_H__
#define __DEFS_H__


#define BOARD_WIDTH  12
#define BOARD_HEIGHT 25

#define BLOCK_WIDTH 4
#define BLOCK_HEIGHT 4

#define NET_BUFFER_LENGTH 256
#define IP_STRING_SIZE 16+1

#define VERSION "0.1.0"

#define LOCALE_KEY_ESCAPE 27

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>


int done;

#endif
