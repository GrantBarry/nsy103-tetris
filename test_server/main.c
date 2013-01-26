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
    sleep(1);
    if (listen(ecoute_fd, 1) != 0) {
        printf("\n\nerreur %d listen socket 'ecoute_fd'\n\n", errno);
        exit(errno);
    }

    connexion_fd = accept(ecoute_fd, (struct sockaddr*)NULL, NULL);
    printf("connexion acceptee\n");

    done = 0;

    while (done == 0) {

        memset(buffer, '\0', sizeof(buffer));
        i = recv(connexion_fd, buffer, sizeof(buffer), MSG_PEEK);

        if (i > 0) {
            recv(connexion_fd, buffer, sizeof(buffer), 0);
            printf("donnees du client : %s\n", buffer);
        }

        printf("saisir une reponse :");
        gets(buffer);

        if (strcmp("quit", buffer) == 0) {
            printf("la commande 'quit' a ete donnee\n");
            done = 1;
            break;
        }
        
        printf("envoie '%s'\n", buffer);
        i = send(connexion_fd, buffer, strlen(buffer), 0);
        printf("%d octets envoyes\n", i);
    }

    printf("ferme les connexions 'connexion_fd' et 'ecoute_fd'\n");
    close(connexion_fd);
    close(ecoute_fd);

    return 0;
}