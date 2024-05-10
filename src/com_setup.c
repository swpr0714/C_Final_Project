#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 2
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
SOCKET client_setup() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed.\n");
        exit(EXIT_FAILURE);
    }

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("140.118.187.96");
    server.sin_port = htons(PORT);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection Failed.\n");
        exit(EXIT_FAILURE);
    }
    printf("Connect!\n");
    return sock;
}

SOCKET *server_setup() {
    WSADATA wsa;
    SOCKET server_fd;
    SOCKET *client_sockets = (SOCKET*) malloc(MAX_CLIENTS * sizeof(SOCKET));
    struct sockaddr_in server, client;
    int addrlen = sizeof(struct sockaddr_in);
    int max_clients = MAX_CLIENTS;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed.\n");
        exit(EXIT_FAILURE);
    }

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize server address structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind the socket to localhost port 8080
    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed.\n");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        printf("Listen failed.\n");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept incoming connections
    for (int i = 0; i < max_clients; ++i) {
        if ((client_sockets[i] = accept(server_fd, (struct sockaddr *)&client, &addrlen)) == INVALID_SOCKET) {
            printf("Accept failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("Connect!\n");
    return client_sockets;
}