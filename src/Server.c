#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "..\header\com_setup.h"
#include "..\header\poker.h"



int main(){
    // Connect
    SOCKET *client_sockets = server_setup();
    Sleep(300);
    // Declare variables
    int **card = shuffle();
    findOrder(card,client_sockets);
    // Game start
    char buffer[BUFFER_SIZE] = "Game Start :D";
    Sleep(50);
    send(client_sockets[0], buffer, strlen(buffer), 0);
    send(client_sockets[1], buffer, strlen(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    // Deal
    Sleep(1200);

    int2str(card[0],buffer);
    printf("User 1 card: %s\n",buffer);
    send(client_sockets[0], buffer, strlen(buffer), 0);

    memset(buffer, 0, BUFFER_SIZE);
    int2str(card[1],buffer);
    printf("User 2 card: %s\n",buffer);
    send(client_sockets[1], buffer, strlen(buffer), 0);
    memset(buffer, 0, BUFFER_SIZE);

    // strcat(buffer,"Your are user 1");
    // Sleep(50);
    // send(client_sockets[0], buffer, strlen(buffer), 0);
    // memset(buffer, 0, BUFFER_SIZE);
    // strcat(buffer,"Your are user 2");
    // Sleep(50);
    // send(client_sockets[1], buffer, strlen(buffer), 0);
    
    ServerEnd:
    WSACleanup();
    return 0;
}