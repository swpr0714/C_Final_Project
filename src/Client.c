#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include "..\header\com_setup.h"
#include "..\header\poker.h"
#include "..\header\client_func.h"
SOCKET g_sock;
#define LOCALHOST "127.0.0.1"
int main(){
    // Connect to server
    char *serveraddr = LOCALHOST;
    // char *serveraddr = "192.168.0.21";
    g_sock = client_setup(serveraddr);  
    //Declare Variable
    int status = 0; 
    char buffer[BUFFER_SIZE] = {0};
    int client_card[26];
    // Wait for dealing
    printf("Wait for other players...\n");
    // Game start
    status = recv(g_sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){printf("Failed to receive."); exit(-1);}
    cls;
    printf("%s\n",buffer);
    memset(buffer,0,sizeof(buffer));
    Sleep(800);
    cls;
    // Deal
    printf("Your deck:\n");
    // Recv card (Can be packged as a function)
    status = recvCard(client_card,buffer);
    if(status!=0){printf("Deal ERROR.\n", status);return -1;}
    // Print card
    printCard(client_card,26);
    chooseType(buffer,client_card);
    // Close socket
    closesocket(g_sock);
    WSACleanup();
    return 0;
}