#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "..\header\com_setup.h"
#include "..\header\poker.h"

SOCKET *g_client_sockets;

int sendCard(int **card, char *buffer){
    int status = 0;
    int2str(card[0],buffer);
    // printf("User 1 card: %s\n",buffer);
    status = send(g_client_sockets[0], buffer, strlen(buffer), 0);
    if (status == SOCKET_ERROR){return 1;}
    memset(buffer, 0, BUFFER_SIZE);
    int2str(card[1],buffer);
    // printf("User 2 card: %s\n",buffer);
    status = send(g_client_sockets[1], buffer, strlen(buffer), 0);
    if (status == SOCKET_ERROR){return 2;}
    memset(buffer, 0, BUFFER_SIZE);
    return 0;
}

int main(){
    int status = 0;
    // Connect
    g_client_sockets = server_setup();
    Sleep(300);
    // Declare variables
    int **card = shuffle();
    findOrder(card,g_client_sockets);
    // Game start
    char buffer[BUFFER_SIZE] = "Game Start :D";
    Sleep(50);
    send(g_client_sockets[0], buffer, strlen(buffer), 0);
    send(g_client_sockets[1], buffer, strlen(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    // Deal
    Sleep(1200);

    status = sendCard(card,buffer);
    if (status!=0){printf("Deal ERROR with code %d.\n", status);return -1;}
    
    ServerEnd:
    WSACleanup();
    return 0;
}