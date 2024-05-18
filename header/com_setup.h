#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 2
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
SOCKET *server_setup();
SOCKET client_setup();