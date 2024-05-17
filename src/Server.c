#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "com_setup.h"
#include "poker.h"
int main(){
    char buffer[BUFFER_SIZE] = {0};
    SOCKET *client_sockets = server_setup();
    // Communication loop
    // while (1) {
    //     for (int i = 0; i < MAX_CLIENTS; ++i) {
    //         int valread = recv(client_sockets[i], buffer, BUFFER_SIZE, 0);
    //         if (valread == 0) {
    //             printf("Client %d disconnected\n", i + 1);
    //             closesocket(client_sockets[i]);
    //             client_sockets[i] = 0;
    //             continue;
    //         }
    //         printf("Received from Client %d: %s\n", i + 1, buffer);
    //         if(buffer[0]=='@'){
    //             printf("User shutdown:(\n");
    //             goto ServerEnd;    
    //         }
    //         // Echo back to the client
    //         send(client_sockets[i], buffer, strlen(buffer), 0);
    //         memset(buffer, 0, BUFFER_SIZE);
    //     }
    // }
    printf("Enter anykey to send: ");
    char a;
    scanf(" %c", &a);
    int **card;
    card = shuffle();
    
    int2str(card[0],buffer);
    send(client_sockets[0], buffer, strlen(buffer), 0);
    memset(buffer, 0, BUFFER_SIZE);
    int2str(card[1],buffer);
    send(client_sockets[1], buffer, strlen(buffer), 0);
    ServerEnd:
    WSACleanup();
    return 0;
}