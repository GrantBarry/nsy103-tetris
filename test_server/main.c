#define DEFAULT_PORT 3000

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int net_send(int socket, char *buffer) {
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
    return total;
}

void send_string(int sock, char * str, int len) {
    int i;
    if (strlen(str) > 0) {
        printf("envoie '%s'\n", str);
        i = net_send(sock, str);
        printf("%d octets envoyes\n", i);            
    }    
}

// Returns 0 if the command is known, else return -1
int auto_response(int sock, char * command) {
    char buffer[2048];
    int x, y;

    printf("enter auto_response\n");

    bzero(buffer, sizeof(buffer));

    // Reply to 100 HELLO
    if (strncmp("100 HELLO", command, strlen("100 HELLO")) == 0) {
        strcpy(buffer, "120 HELLO ");
        x = strlen("100 HELLO ");
        while (command[x] != '\0') {
            buffer[x] = command[x];
            x++;
        }
        command[x] = '\0';
        send_string(sock, buffer, strlen(buffer));
        return 0;
    }

    // Reply to 110 READY
    if (strcmp("110 READY", command) == 0) {
        strcpy(buffer, "130 GO 1 2");
        send_string(sock, buffer, strlen(buffer));
        return 0;
    }

    // Reply to 280 DUMP
    if (strcmp("280 DUMP", command) == 0) {
        strcpy(buffer, "301 OK ");
        for (y = 0; y < 25; y++) {
            for (x = 0; x < 12; x++) {          
                if (y > 23) {
                    strcat(buffer, "1");
                } else {
                    strcat(buffer, "0");
                }            
            }
        }
        strcat(buffer, " 1 0 0 2");
        send_string(sock, buffer, strlen(buffer));
        return 0;
    }

    if (strcmp(command, "200 LEFT") == 0 ||
        strcmp(command, "210 RIGHT") == 0 ||
        strcmp(command, "220 DOWN") == 0 ||
        strcmp(command, "240 ROTATE_R") == 0 ||
        strcmp(command, "250 ROTATE_L") == 0 ||
        strcmp(command, "260 INVERSE") == 0) {
        strcpy(buffer, "300 OK");
        send_string(sock, buffer, strlen(buffer));
        return 0;        
    }

    // Reply to 230 FULLDOWN
    if (strcmp("230 FULLDOWN", command) == 0) {
        y = 1+(rand() % 5); // Generate a new random piece
        x = rand() % 5;
        printf("x = %d and y = %d\n", x, y);
        if (x == 4) {            
            sprintf(buffer, "330 OK %d 1 010101010101", y);
        } else {
            sprintf(buffer, "310 OK %d", y);
        }
        send_string(sock, buffer, strlen(buffer));
        return 0;
    }

    return -1;
}

int main(int argc, char *argv[])
{
    int ecoute_fd = 0;
    int connexion_fd = 0;
    int i;
    int done;
    struct sockaddr_in serv_addr;
    char buffer[1025];

    printf("Serveur Interactif\n\nSaisir 'quit' pour quitter\n\n");

    printf("creation du socket 'ecoute_fd'\n");
    ecoute_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (ecoute_fd == -1) {
        printf("\n\nerreur %d creation socket 'ecoute_fd'\n\n", errno);
        exit(errno);
    }

    memset(&serv_addr, '\0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(DEFAULT_PORT); 

    printf("bind socket 'ecoute_fd' sur port %d\n", DEFAULT_PORT);
    if (bind(ecoute_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) != 0) {
        printf("\n\nerreur %d bind socket 'ecoute_fd'\n\n", errno);
        exit(errno);
    }

    printf("listen 'ecoute_fd'\n");
    if (listen(ecoute_fd, 1) != 0) {
        printf("\n\nerreur %d listen socket 'ecoute_fd'\n\n", errno);
        exit(errno);
    }

    connexion_fd = accept(ecoute_fd, (struct sockaddr*)NULL, NULL);
    printf("connexion acceptee\n");

    done = 0;

    while (done == 0) {
        bzero(buffer, sizeof(buffer));
        recv(connexion_fd, buffer, sizeof(buffer), 0);
        printf("donnees du client : %s\n", buffer);
        sleep(1);

        if (auto_response(connexion_fd, buffer) != 0) {
            printf("auto_response return != 0\n");

            printf("saisir une reponse :");
            gets(buffer);

            if (strcmp("quit", buffer) == 0) {
                printf("la commande 'quit' a ete donnee\n");
                strcpy(buffer, "140 END");
                send_string(connexion_fd, buffer, strlen(buffer));
                done = 1;
                break;
            }

            send_string(connexion_fd, buffer, strlen(buffer));
        }
    }

    printf("ferme les connexions 'connexion_fd' et 'ecoute_fd'\n");
    close(connexion_fd);
    close(ecoute_fd);

    return 0;
}
