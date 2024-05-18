#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include "..\header\com_setup.h"
#include "..\header\poker.h"
int main(){
    // Connect to server
    char *serveraddr = "192.168.0.21";
    SOCKET sock = client_setup(serveraddr);  
    //Declare Variable
    int status; 
    char buffer[BUFFER_SIZE] = {0};
    int client_card[26];
    // Wait for dealing
    printf("Wait for other players...\n");
    status = recv(sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){printf("Failed to receive."); exit(-1);}
    cls;
    printf("%s\n",buffer);
    memset(buffer,0,sizeof(buffer));
    Sleep(800);
    cls;
    printf("Your deck:\n");
    // Recv card (Can be packged as a function)
    status = recv(sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){printf("Failed to receive card."); exit(-1);}
    str2int(client_card,buffer);
    memset(buffer,0,sizeof(buffer));
    // Print card
    printCard(client_card,26);
    //
    // status = recv(sock,buffer,BUFFER_SIZE,0);
    // if(status==SOCKET_ERROR){printf("Failed to receive card."); exit(-1);}
    // printf("%s\n",buffer);
    // Close socket
    closesocket(sock);
    WSACleanup();
    return 0;
}