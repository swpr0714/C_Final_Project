#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "..\header\com_setup.h"
#include "..\header\poker.h"
#include "..\header\server_func.h"
int main(){
    int prev_card[5]={-1,-1,-1,-1,-1};
    extern SOCKET g_server_fd;
    extern SOCKET *g_client_sockets; 
    int status = 0;
    // Connect
    server_setup();
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
    status = sendCard(card,buffer,0);
    status = sendCard(card,buffer,1);
    if (status!=0){printf("Deal ERROR with code %d.\n", status);return -1;}
    //Player 1 playing
    recvType(0, buffer);
    recvCard(0,buffer,card,prev_card);
    sendCard(card,buffer,0);
    for(int i = 0; i <5; i++){
        printf("%d ", prev_card[i]);
    }
    serverShutdown();
    return 0;
}