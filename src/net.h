#ifndef __NET_H__
#define __NET_H__

#include "defs.h"

int net_connected;
int net_socket;
struct sockaddr_in net_socket_address;
char net_last_command[NET_BUFFER_LENGTH];

void net_init(void);
void net_connect(char * ip, int port);
void net_disconnect(void);

#endif