
#include "net.h"

void net_init(void) {
	net_connected = 0;
}

void net_connect(void) {
	net_connected = 1;
}

void net_disconnect(void) {
	net_connected = 0;
}