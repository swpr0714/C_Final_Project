#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "..\header\com_setup.h"
#include "..\header\poker.h"
#include "..\header\server_func.h"

int end(int status, char *buffer){
    switch(status){
            case 0:
                strcat(buffer,"#");
                send(g_client_sockets[0], buffer, BUFFER_SIZE, 0);
                send(g_client_sockets[1], buffer, BUFFER_SIZE, 0);
                break;
            case 1:
                strcat(buffer,"A");
                send(g_client_sockets[0], buffer, BUFFER_SIZE, 0);
                send(g_client_sockets[1], buffer, BUFFER_SIZE, 0);
                break;
            case 2:
                strcat(buffer,"B");
                send(g_client_sockets[0], buffer, BUFFER_SIZE, 0);
                send(g_client_sockets[1], buffer, BUFFER_SIZE, 0);
                break;
            case -1:
                printf("Return -1\n");
                return -1;
        }
        serverShutdown();
        return 0;
}
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

    while(1){
        for(int i=0;i<2; i++){
            printf("user %d start\n", i);
            if(mode==0){
                mode = recvType(i, buffer);
            }
            else{
                clbuf;
                itoa(mode, buffer, 10);
                printf("Mode = %s\n", buffer);
                send(g_client_sockets[i], buffer, strlen(buffer), 0);
            }
            recvCard(i,buffer,card,prev_card,mode);
            status = checkWin(card);
            // printf("Check win %d", status);
            if(status){
                // printf("status = %d\n", status);
                end(status, buffer);
            }
            clbuf;
            int a;
            strcat(buffer,"#");
            send(g_client_sockets[i], buffer, BUFFER_SIZE, 0);
            // printf("send #\n");
            clbuf;
            status = sendCard(card,buffer,i);
            
            if(status==-1){
                printf("Send fail");
            }
            mode = checkPass(mode,prev_card);
            printf("user %d finish\n", i);
        }
    }
    return 0;
}

