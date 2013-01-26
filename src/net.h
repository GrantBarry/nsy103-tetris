#ifndef __NET_H__
#define __NET_H__

#include "defs.h"

int net_connected;
int net_socket;
struct sockaddr_in net_socket_address;
char net_last_command[NET_BUFFER_LENGTH];

void net_init(void);
void net_connect(char * ip, int port);
void net_send(int socket, char * buffer);
int net_recieve(int socket, char * buffer, int length);
void net_send_name(char * name);
void net_send_ready(void);
void net_send_left(void);
void net_send_right(void);
void net_send_down(void);
void net_send_full_down(void);
void net_send_rotate_right(void);
void net_send_rotate_left(void);
void net_send_invert(void);
void net_send_pass();
void net_send_dump_request();
void net_send_enemy_dump_request();
void net_get_response(int * code, char * command, char * data);
void net_disconnect(void);

#endif