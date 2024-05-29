#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#define PORT 6312
#define BUFFER_SIZE 256
#define MAX_CLIENTS 2
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

SOCKET g_server_fd;
SOCKET *g_client_sockets; 

SOCKET client_setup(char *serveraddr) {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed.\n");
        exit(-1);
    }

    // Create Socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        exit(-1);
    }
    printf("Server IP: %s\n",serveraddr);
    // Initialize server address structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(serveraddr);
    server.sin_port = htons(PORT);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection Failed.\n");
        exit(-1);
    }
    printf("Connect Successful!\n");
    return sock;
}

int *server_setup() {
    WSADATA wsa;
    g_client_sockets = (SOCKET*) malloc(MAX_CLIENTS * sizeof(SOCKET));
    struct sockaddr_in server, client;
    int addrlen = sizeof(struct sockaddr_in);
    int max_clients = MAX_CLIENTS;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed.\n");
        exit(-1);
    }

    // Create Socket
    if ((g_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        exit(-1);
    }

    // Initialize server address structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind
    if (bind(g_server_fd, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed.\n");
        exit(-1);
    }

    // Listen
    if (listen(g_server_fd, 3) == SOCKET_ERROR) {
        printf("Listen failed.\n");
        exit(-1);
    }

    printf("Server listening on PORT %hu\n", PORT);

    // Accept
    for (int i = 0; i < max_clients; ++i) {
        if ((g_client_sockets[i] = accept(g_server_fd, (struct sockaddr *)&client, &addrlen)) == INVALID_SOCKET) {
            printf("Accept failed.\n");
            exit(-1);
        }
        else{
            printf("User %d Connect!\n",i+1);
        }
    }
    printf("Connect Successful!\n");
    return 0;
}