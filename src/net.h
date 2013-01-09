#ifndef __NET_H__
#define __NET_H__

#include "defs.h"

int net_connected;

void net_init(void);
void net_connect(void);
void net_disconnect(void);

#endif