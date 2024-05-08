/*
	This brief code for internet connection is obtained and modified from the Microsoft
	website for the term project of NTUST ME2008303 class, 2019.
	Author: Yu-Hsuan Su
			National Taiwan University of Science and Technology
			Department of Mechanical Engineering
*/

#include <stdio.h>
#include "..\include\inet.h"

#pragma warning(disable:4996)

// #define CLIENT
#define SERVER
#define DEBUG

int __cdecl main(int argc, char **argv)
{
#ifdef CLIENT
	char *ipaddr, str[512] = "Client connecting...\n";

	// server's ip address for testing and debugging
	char ipaddr_test[] = "140.118.199.150";

	// Validate the arguments
	if (argc != 2) {
#ifdef DEBUG
		// using default ip address for testing
		ipaddr = ipaddr_test;
#else
		printf("usage: %s server-name\n", argv[0]);
		return 1;
#endif
	}
	else
		ipaddr = argv[1];

	// try to connect to server
	printf("%s", str); client_connect(ipaddr);

	// interactive process
	do {
		// prompt for input
		printf(" <A> : "); fgets(str, sizeof(str), stdin);

		// To end connection, put @ as the first character.
		if (str[0] == '@') return 0;

		// remove the newline character obtained by fgets()
		int i = 0; while (str[i] != '\n') i++; str[i] = '\0';

		// send message to server
		send_str(str);

		// receive response from server
		recv_str();
	} while (1);

	// end connection
	inet_shutdown();
#endif // CLIENT

#ifdef SERVER

	char str[512] = "Server waiting...\n";

	// waiting for client to connect
	printf("%s", str); server_listen();

	do {
		// receive request from client
		recv_str();

		// prompt for input
		printf(" <A> : "); fgets(str, sizeof(str), stdin);

		// To end connection, put @ as the first character
		if (str[0] == '@') return 0;

		// remove the newline character obtained by fgets()
		int i = 0;  while (str[i] != '\n') i++; str[i] = '\0';

		// send response to client
		send_str(str);
	} while (1);

	// end connection
	inet_shutdown();
#endif // SERVER
}