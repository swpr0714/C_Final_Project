#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#define PORT 6312
#define BUFFER_SIZE 256
#define MAX_CLIENTS 2
#define clbuf memset(buffer, 0, BUFFER_SIZE)
#define cls system("cls")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
extern SOCKET g_server_fd;
extern SOCKET *g_client_sockets; 
int *server_setup();
SOCKET client_setup();