#include "net.h"

void net_init(void) {
	int flag;
	struct timeval tv;
	net_connected = 0;

	net_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (net_socket < 0) {
		error("ERROR opening socket");
	}
	printf("[net_init] net_socket set to %d\n", net_socket);

	// Set a timout option on our socket
	// tv.tv_sec = 5;
	// tv.tv_usec = 0;
	// setsockopt(net_socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(struct timeval));
}

void net_connect(char *ip, int port) {
	memset(&net_socket_address, 0, sizeof(net_socket_address));
	net_socket_address.sin_family = AF_INET;
	net_socket_address.sin_addr.s_addr = inet_addr(ip);
	net_socket_address.sin_port = htons(port);

	if (connect(net_socket, (struct sockaddr *)&net_socket_address, sizeof(net_socket_address)) < 0) {
		error("ERROR connecting");
	}
	printf("[net_connect] connected using port %d\n", port);
	net_connected = 1;
}

void net_disconnect(void) {
	net_connected = 0;
	close(net_socket);
	printf("[net_disconnect] closed socket\n");
}

void net_send(int socket, char *buffer) {
	int total = 0;
	int length = strlen(buffer);
	int bytesleft = length;
	int n;

	while (total < length) {
		n = send(socket, buffer + total, bytesleft, MSG_DONTWAIT);
		if (n == -1) {
			break;
		}
		total += n;
		bytesleft -= n;
	}
}

// Le client salue le serveur et lui donne le nom qu'il choisi pour jouer
// 100 HELLO <nom_client>
void net_send_name(char *name) {
	char sendBuffer[NET_BUFFER_LENGTH];
	memset(sendBuffer, '\0', sizeof(sendBuffer));
	sprintf(sendBuffer, "100 HELLO %s", name);

	net_send_command(sendBuffer);

	if (net_current_code != 120) {
		sprintf(sendBuffer, "[net_send_name] ERROR! Server did not accept the name (wrong return code) : %d\n", net_current_code);
		error(sendBuffer);
	}
	if (strcmp("HELLO", net_current_command) != 0) {
		sprintf(sendBuffer, "[net_send_name] ERROR! Server did not accept the name (wrong command) %s\n", net_current_command);
		error(sendBuffer);
	}
	if (strcmp(name, net_current_data) != 0) {
		error("[net_send_name] ERROR! Server did not accept the name (wrong name)\n");
	}
}

void net_send_command(char * send_command) {
	net_send(net_socket, send_command);
	net_wait_for_response();
}

void net_wait_for_response(void) {
	char receiveBuffer[NET_BUFFER_LENGTH];
	bzero(receiveBuffer, sizeof(receiveBuffer));
	if (recv(net_socket, receiveBuffer, sizeof(receiveBuffer), 0) == -1) {
		// An error occured, so set the return command to 501 so that the game requests a DUMP
		net_current_code = 501;
		return;
	}

	net_current_code = 0;
	bzero(net_current_command, sizeof(net_current_command));
	bzero(net_current_data, sizeof(net_current_data));
	sscanf(receiveBuffer, "%d %s %[^\n]", &net_current_code, net_current_command, net_current_data);
}