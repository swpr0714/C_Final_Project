//
// For the purpose of the term project of ME2008301, this code (inet.cpp) is
// slightly modified from the code obtained from Microsoft's website:
// https://docs.microsoft.com/en-us/windows/desktop/winsock/complete-client-code
//

#define WIN32_LEAN_AND_MEAN
#undef UNICODE

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512+1
#define DEFAULT_PORT "27015"

SOCKET ListenSocket = INVALID_SOCKET;
SOCKET theSocket = INVALID_SOCKET;

int client_connect(char * ipaddr) {
	WSADATA wsaData;

	struct addrinfo *result = NULL, *ptr = NULL, hints;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);  //startup(version, &wsadata)
	if (iResult != 0) {  //檢查開啟
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}
	// hints 除了AI_Family, AI_Socktype, AI_Protocal和AI_Flags 其他應為0或NULL 所以先清空記憶體再設置 
	ZeroMemory(&hints, sizeof(hints));  //清空記憶體
	hints.ai_family = AF_INET;  // 使用IPv4協議
	hints.ai_socktype = SOCK_STREAM; // 指定雙向數據流
	hints.ai_protocol = IPPROTO_TCP; // 使用TCP協議

	// Resolve the server address and port
	iResult = getaddrinfo(ipaddr, DEFAULT_PORT, &hints, &result); // Client應設置Addr及Port
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
		// Create a SOCKET for connecting to server
		theSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (theSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect(theSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(theSocket);
			theSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (theSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}
	return 0;
}

int server_listen() {
	WSADATA wsaData;
	int iResult;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Accept a client socket
	theSocket = accept(ListenSocket, NULL, NULL);
	if (theSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// No longer need server socket
	closesocket(ListenSocket);
	return 0;
}

int send_str(char * str) {
	int iResult, iRecvResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Send an initial buffer
	iResult = send(theSocket, str, (int)strlen(str), 0);

	if (iResult > 0) {
		// wait for confirmation
		iRecvResult = recv(theSocket, recvbuf, recvbuflen, 0);
		if (iRecvResult == SOCKET_ERROR) {
			printf("Connection lost: %d\n", WSAGetLastError());
			closesocket(theSocket);
			WSACleanup();
			return 1;
		}
		return 0;
	}
	else if (iResult == 0) {
		printf("Connection closing...\n"); return 1;
	}
	else {
		printf("No response error: %d\n", WSAGetLastError());
		closesocket(theSocket);
		WSACleanup();
		return 1;
	}
}

int recv_str() {
	int iResult;
	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	char replied[] = "Received!";

	iResult = recv(theSocket, recvbuf, recvbuflen, 0);
	if (iResult > 0) {
		// received
		recvbuf[iResult] = 0;

		// display incoming message received
		printf(" <B> : %s\n", recvbuf);

		// Echo back to the sender
		iSendResult = send(theSocket, replied, 11, 0);
		if (iSendResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(theSocket);
			WSACleanup();
			return 1;
		}
	}
	else if (iResult == 0)
		printf("Connection closing...\n");
	else {
		printf("recv failed with error: %d\n", WSAGetLastError());
		closesocket(theSocket);
		WSACleanup();
		return 1;
	}
	return 0;
}

int inet_shutdown() {
	int iResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// shutdown the connection since no more data will be sent
	iResult = shutdown(theSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(theSocket);
		WSACleanup();
		return 1;
	}

	// Receive until the peer closes the connection
	do {
		iResult = recv(theSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			printf("rcvd: %s, Bytes received: %d\n", recvbuf, iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());
	} while (iResult > 0);

	// cleanup
	closesocket(theSocket);
	WSACleanup();

	return 0;
}