
#include "net.h"

void net_init(void) {
	net_connected = 0;

	net_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (net_socket < 0) {
		error("ERROR opening socket");
	}
}

void net_connect(char * ip, int port) {
	memset(&net_socket_address, 0, sizeof(net_socket_address));
	net_socket_address.sin_family = AF_INET;
	net_socket_address.sin_addr.s_addr = inet_addr(ip);
	net_socket_address.sin_port = htons(port);
	
	if (connect(net_socket, &net_socket_address, sizeof(net_socket_address)) < 0) {
		error("ERROR connecting");
	}

	net_connected = 1;
}

void net_disconnect(void) {
	net_connected = 0;
	close(net_socket);
}

void net_send(int socket, char * buffer) {
	int ret;
	
	// Store a copy of the last net send command
	memset(lastNetCommand, '\0', sizeof(lastNetCommand));
	strcpy(lastNetCommand, buffer);
	
	ret = write(socket, buffer, strlen(buffer));
	if (ret  < 0) {
		error("ERROR writing to socket");
	}
}

void net_read(int socket, char * buffer) {
	int ret;
	memset(buffer, '\0', sizeof(buffer));
	ret = read(socket, buffer, sizeof(buffer)-1);
	if (ret < 0) {
		error("ERROR reading from socket");
	}
}

int net_recieve(int socket, char * buffer) {
	memset(buffer, '\0', sizeof(buffer));
	return recv(socket, buffer, sizeof(buffer)-1, 0);
}

// Le client salue le serveur et lui donne le nom qu'il choisi pour jouer
// 100 HELLO <nom_client>
void net_send_name(char * name) {
	char sendBuffer[NET_BUFFER_LENGTH];
	char receiveBuffer[NET_BUFFER_LENGTH];
	
	memset(sendBuffer, '\0', sizeof(sendBuffer));
	asprintf(sendBuffer, "100 HELLO %s", name);
	net_send(net_socket, sendBuffer);
	
	net_read(net_socket, receiveBuffer);
	if (strcmp(sendBuffer, receiveBuffer) != 0) {
		error("ERROR server didn't accept the correct name");
	}
}

// Le client est prêt pour le début de la partie
// 110 READY
void net_send_ready(void) {
	net_send(net_socket, "100 READY");
}

// Déplacement de la pièce vers la gauche
// 200 LEFT
void net_send_left(void) {
	net_send(net_socket, "200 LEFT");
}

// Déplacement de la pièce vers la droite
// 210 RIGHT
void net_send_right(void) {
	net_send(net_socket, "210 RIGHT");
}

// Déplacement de la pièce d'une ligne vers le bas
// 220 DOWN
void net_send_down(void) {
	net_send(net_socket, "220 DOWN");
}

// Déplacement de la pièce jusqu'au bas du tableau
// 230 FULLDOWN
void net_send_full_down(void) {
	net_send(net_socket, "230 FULLDOWN");
}

// Rotation de la pièce dans le sens horaire
// 240 ROTATE_R
void net_send_rotate_right(void) {
	net_send(net_socket, "240 ROTATE_R");
}

// Rotation de la pièce dans le sens anti-horaire
// 250 ROTATE_L
void net_send_rotate_left(void) {
	net_send(net_socket, "250 ROTATE_L");
}

// Symétrie horizontale de la pièce
// 260 INVERSE
void net_send_invert(void) {
	net_send(net_socket, "260 INVERSE");
}

// Ne rien faire
// 270 PASS
void net_send_pass() {
	net_send(net_socket, "270 PASS");
}

// Demander au serveur une copie du tableau et des pièces
// 280 DUMP
void net_send_dump_request() {
	net_send(net_socket, "280 DUMP");
}

// Demander au serveur une copie du tableau et des pièces de l'adversaire
// 290 DUMPENEMY
void net_send_enemy_dump_request() {
	net_send(net_socket, "290 DUMPENEMY");
}