#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include "com_setup.h"
#include "poker.h"
int main(){
    char buffer[BUFFER_SIZE] = {0};
    char *serveraddr = "172.20.10.4";
    SOCKET sock = client_setup(serveraddr);  
    int status; 
    // Communication loop
    // while (1) {
    //     printf("Enter a message: ");
    //     fgets(buffer, BUFFER_SIZE, stdin);
    //     // Send message to server
    //     status = send(sock, buffer, strlen(buffer), 0);
    //     if(status==SOCKET_ERROR) {
    //         printf("ERROR: Server No Response\n");
    //         break;
    //     }
    //     if(buffer[0]=='@'){
    //         printf("Shutdown :)\n");
    //         break;
    //     }
    //     memset(buffer, 0, BUFFER_SIZE);
    //     // Receive message from server
    //     status = recv(sock, buffer, BUFFER_SIZE, 0);
    //     printf("Server response: %s\n", buffer);
    // }
    int client_card[26];
    printf("Waiting for message...\n");
    status = recv(sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){printf("Failed to receive."); exit(-1);}
    system("cls");
    // printf("%s",buffer);
    str2int(client_card,buffer);
    printCard(client_card,26);
    // Close socket
    closesocket(sock);
    WSACleanup();
    return 0;
}