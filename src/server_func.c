#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "..\header\com_setup.h"
#include "..\header\poker.h"
SOCKET *g_client_sockets;
#define BUFFER_SIZE 1024
int sendCard(int **card, char *buffer, int client){
    int status = 0;
    clbuf;
    int2str(card[client],buffer);
    status = send(g_client_sockets[client], buffer, strlen(buffer), 0);
    if (status == SOCKET_ERROR){return 1;}
    clbuf;
    return 0;
}
int recvType(int i, char *buffer){
    Sleep(1000);
    memset(buffer, 0, sizeof(buffer));
    strcat(buffer,"@");
    send(g_client_sockets[i], buffer, strlen(buffer), 0);
    int status = recv(g_client_sockets[i],buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){printf("Failed to receive type.\n"); return 1;}
    printf("Card mode is %s.\n",buffer);
    return 0;
}
int serverShutdown(){
    printf("Closing...\n");
    closesocket(g_client_sockets[0]);
    closesocket(g_client_sockets[1]);
    closesocket(g_server_fd);
    WSACleanup();
    printf("System has shutdown.\n");
    return 0;
}

int recvCard(int client, char *buffer, int **card, int *prev_card){
    clbuf;
    int cardset[5];
    int status = recv(g_client_sockets[client],buffer,BUFFER_SIZE,0);
    printf("RECV: %s\n",buffer);
    str2int(cardset,buffer);
    clbuf;
    strcat(buffer, "*");
    send(g_client_sockets[client], buffer, strlen(buffer),0);
    // quickSort(cardset,0,5);
    for(int i=0;i<5;i++){
        printf("%d ", cardset[i]);
    }
    if (cardset[4] < prev_card[4]){
        printf("Card set is smaller than previous.\n");
        return 1;
    }
    for(int i=0;i<5;i++){
        prev_card[i]=cardset[i];
        if(cardset[i]==-1){continue;}
        card[client][cardset[i]]=-1;
    }
    printf("Success.\n");
    return 0;
}