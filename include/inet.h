#pragma once
#include <winsock2.h>

extern int client_connect(char * ipaddr);
extern int server_listen();
extern int send_str(char * str);
extern int recv_str();
extern int inet_shutdown();

extern SOCKET theSocket, ListenSocket;
extern char recvbuf[513];
