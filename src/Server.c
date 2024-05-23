#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "..\header\com_setup.h"
#include "..\header\poker.h"
#include "..\header\server_func.h"
int main(){
    srand(time(NULL));
    int prev_card[5]={-1,-1,-1,-1,-1};
    extern SOCKET g_server_fd;
    extern SOCKET *g_client_sockets; 
    int status = 0;
    int mode = 0;
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
    for(int i=0;i<2; i++){
        printf("user %d start\n", i);
        if(mode==0){
            mode = recvType(i, buffer);
        }
        else{
            clbuf;
            itoa(mode, buffer, 10);
            send(g_client_sockets[i], buffer, strlen(buffer), 0);
        }
        Sleep(1000);
        recvCard(i,buffer,card,prev_card,mode);

        if(sendCard(card,buffer,i)==-1){
            printf("Send fail");
        }
        printf("user %d finish\n", i);
    }
    for(int i=0;i<2; i++){
        printf("user %d start\n", i);
        if(mode==0){
            mode = recvType(i, buffer);
        }
        else{
            clbuf;
            itoa(mode, buffer, 10);
            send(g_client_sockets[i], buffer, strlen(buffer), 0);
        }
        recvCard(i,buffer,card,prev_card,mode);
        if(sendCard(card,buffer,i)==-1){
            printf("Send fail");
        }
        printf("user %d finish\n", i);
    }
    
    serverShutdown();
    return 0;
}