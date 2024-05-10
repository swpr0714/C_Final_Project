#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "com_setup.h"
    
int main(){
    char buffer[BUFFER_SIZE] = {0};
    SOCKET sock = client_setup();  
    // SOCKET sock; 
    int valread; 
    // Communication loop
    while (1) {
        printf("Enter a message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        // Send message to server
        send(sock, buffer, strlen(buffer), 0);
        memset(buffer, 0, BUFFER_SIZE);
        // Receive message from server
        valread = recv(sock, buffer, BUFFER_SIZE, 0);
        printf("Server response: %s\n", buffer);
    }

    // Close socket
    closesocket(sock);
    WSACleanup();
    return 0;
}