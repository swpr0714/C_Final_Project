/******************************/
/*此檔案皆為B11131016鄧盛文所寫*/
/******************************/

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "..\header\com_setup.h"
#include "..\header\poker.h"
SOCKET* g_client_sockets;
int sendCard(int** card, char* buffer, int client) {
    int status = 0;
    clbuf;
    int2str(card[client], buffer, 26);
    status = send(g_client_sockets[client], buffer, BUFFER_SIZE, 0);
    if (status == SOCKET_ERROR) {
        return 1;
    }
    clbuf;
    return 0;
}
int recvType(int i, char* buffer) {
    int ret = -1;
    memset(buffer, 0, sizeof(buffer));
    strcat(buffer, "@");
    send(g_client_sockets[i], buffer, BUFFER_SIZE, 0);
    int status = recv(g_client_sockets[i], buffer, BUFFER_SIZE, 0);
    if (status == SOCKET_ERROR) {
        printf("Failed to receive type.\n");
        return -1;
    }
    printf("Card mode is %s.\n", buffer);
    ret = atoi(buffer);
    return ret;
}

int recvCard(int client, char* buffer, int** card, int* prev_card, int mode) {
    int* cardset = malloc(5 * sizeof(int));
    clbuf;
    // Send previous cardset
    int2str(prev_card, buffer, 5);
    send(g_client_sockets[client], buffer, BUFFER_SIZE, 0);
    clbuf;
recv_restart:
    // Recv clients cardset
    int status = recv(g_client_sockets[client], buffer, BUFFER_SIZE, 0);
    if (status == SOCKET_ERROR) {
        printf("Recv ERROR.\n");
        return -1;
    }
    status = str2int(cardset, buffer);
    clbuf;
    strcat(buffer, "*");
    send(g_client_sockets[client], buffer, BUFFER_SIZE, 0);
    clbuf;
    Sort(cardset, 5);
    // Print clients cardset
    printf("User throw: ");
    for (int i = 0; i < 5; i++) {
        if (cardset[i] != -1) {
            printf("%d", card[client][cardset[i]]);
        } else {
            printf("-1");
        }
        if (i != 4) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
    // Print previous cardset
    printf("Prev: ");
    for (int i = 0; i < 5; i++) {
        if (cardset[i] == -1) {
            prev_card[i] = -1;
        } else if (cardset[i] == -3) {
            prev_card[i] = -1;
        } else {
            prev_card[i] = card[client][cardset[i]];
        }
        printf("%d ", prev_card[i]);
    }
    printf("\n");
    // Delete card
    for (int i = 0; i < 5; i++) {
        if (cardset[i] != -1) {
            card[client][cardset[i]] = -2;
        }
    }
    // Server response
    strcat(buffer, "*");
    send(g_client_sockets[client], buffer, BUFFER_SIZE, 0);
    free(cardset);
    return 0;
}
int checkPass(const int mode, int* prev) {
    int temp = mode;
    for (int i = 0; i < 5; i++) {
        if (prev[i] != -1) {
            return mode;
        }
    }
    return 0;
}

int checkWin(int** card) {
    int status = 1;
    for (int i = 0; i < 26; i++) {
        if (card[0][i] == -2) {
            continue;
        } else {
            status = 0;
            break;
        }
    }
    if (status) {
        return 1;
    }
    for (int i = 0; i < 26; i++) {
        if (card[1][i] != -2) {
            return 0;
        }
    }
    return 2;
}

int serverShutdown() {
    printf("Closing...\n");
    closesocket(g_client_sockets[0]);
    closesocket(g_client_sockets[1]);
    closesocket(g_server_fd);
    WSACleanup();
    printf("System has shutdown.\n");
    return 0;
}

int end(int status, char* buffer) {
    clbuf;
    switch (status) {
        case 0:
            strcat(buffer, "#");
            send(g_client_sockets[0], buffer, BUFFER_SIZE, 0);
            send(g_client_sockets[1], buffer, BUFFER_SIZE, 0);
            break;
        case 1:
            strcat(buffer, "A");
            send(g_client_sockets[0], buffer, BUFFER_SIZE, 0);
            send(g_client_sockets[1], buffer, BUFFER_SIZE, 0);
            break;
        case 2:
            strcat(buffer, "B");
            send(g_client_sockets[0], buffer, BUFFER_SIZE, 0);
            send(g_client_sockets[1], buffer, BUFFER_SIZE, 0);
            break;
        case -1:
            return -1;
    }
    serverShutdown();
    return 0;
}
