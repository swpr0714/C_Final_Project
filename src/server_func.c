#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "..\header\com_setup.h"
#include "..\header\poker.h"
SOCKET *g_client_sockets;
#define BUFFER_SIZE 1024
int sendCard(int **card, char *buffer){
    int status = 0;
    int2str(card[0],buffer);
    status = send(g_client_sockets[0], buffer, strlen(buffer), 0);
    if (status == SOCKET_ERROR){return 1;}
    memset(buffer, 0, BUFFER_SIZE);
    int2str(card[1],buffer);
    status = send(g_client_sockets[1], buffer, strlen(buffer), 0);
    if (status == SOCKET_ERROR){return 2;}
    memset(buffer, 0, BUFFER_SIZE);
    return 0;
}
int recvType(int i, char *buffer){
    Sleep(2000);
    memset(buffer, 0, sizeof(buffer));
    strcat(buffer,"@");
    send(g_client_sockets[i], buffer, strlen(buffer), 0);
    int status = recv(g_client_sockets[i],buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){printf("Failed to receive type.\n"); return 1;}
    printf("Card mode is %s.",buffer);
    return 0;
}