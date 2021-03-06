#ifndef __NET_H__
#define __NET_H__

#include "defs.h"

int net_connected;
int net_socket;
struct sockaddr_in net_socket_address;
int net_current_code;
char net_current_command[NET_BUFFER_LENGTH];
char net_current_data[NET_BUFFER_LENGTH];

void net_init(void);
void net_connect(char *ip, int port);
void net_send(int socket, char *buffer);
void net_send_name(char *name);
void net_wait_for_response();
void net_send_command(char * send_command);
void net_disconnect(void);

#endif