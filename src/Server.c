#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "..\header\com_setup.h"
#include "..\header\poker.h"
#include "..\header\server_func.h"

int main(int argc, char** argv) {
    // Initialize
    srand(time(NULL));
    // Decleare Variables
    int prev_card[5] = {-1, -1, -1, -1, -1};
    int** card;
    extern SOCKET g_server_fd;
    extern SOCKET* g_client_sockets;
    int status = 0;
    int mode = 0;
    // Initialize and Connect
    server_setup();
    Sleep(300);
    // TEST Cardset or Shuffle
    if (argc == 2 && strcmp(argv[1], "TEST") == 0) {
        card = (int**)malloc(2 * sizeof(int*));
        card[0] = (int*)malloc(26 * sizeof(int));
        card[1] = (int*)malloc(26 * sizeof(int));
        int defaultcard[2][26] = {
            {0, 1, 2, 3, 4, 6, 7, 8, 10, 12, 16, 18, 24, 25, 28, 29, 32, 33, 36, 37, 38, 41, 44, 45, 46, 47},
            {5, 9, 11, 13, 14, 15, 17, 19, 20, 21, 22, 23, 26, 27, 30, 31, 34, 35, 39, 40, 42, 43, 48, 49, 50, 51}};
        for (int i = 0; i < 52; i++) {
            card[i / 26][i % 26] = defaultcard[i / 26][i % 26];
        }
    } else {
        card = shuffle();
    }
    // Find which client is the 1st player
    findOrder(card, g_client_sockets);

    // Game start
    char buffer[BUFFER_SIZE] = "Game Start :D";
    Sleep(50);
    send(g_client_sockets[0], buffer, strlen(buffer), 0);
    send(g_client_sockets[1], buffer, strlen(buffer), 0);
    memset(buffer, 0, sizeof(buffer));

    // Deal
    Sleep(1200);
    status = sendCard(card, buffer, 0);
    status = sendCard(card, buffer, 1);
    if (status != 0) {
        printf("Deal ERROR with code %d.\n", status);
        return -1;
    }

    while (1) {
        for (int i = 0; i < 2; i++) {
            printf("user %d start\n", i);
            // Recv or send card type
            if (mode == 0) {
                mode = recvType(i, buffer);
                if (mode == -1) {
                    goto end;
                }
            } else if (mode == -1) {
                goto end;
            } else {
                clbuf;
                itoa(mode, buffer, 10);
                printf("Mode = %s\n", buffer);
                send(g_client_sockets[i], buffer, strlen(buffer), 0);
            }
            // Recv clients cards and delete from the cardset
            status = recvCard(i, buffer, card, prev_card, mode);
            if (status == -1) {
                goto end;
            }
            // Check if the player is win
            status = checkWin(card);
            if (status) {
                end(status, buffer);
                goto end;
            }
            // Ask player continue
            clbuf;
            strcat(buffer, "#");
            send(g_client_sockets[i], buffer, BUFFER_SIZE, 0);
            clbuf;
            status = sendCard(card, buffer, i);
            if (status == -1) {
                printf("Send fail");
                goto end;
            }
            // Check if the player pass, if yes, set mode = 0
            mode = checkPass(mode, prev_card);
            printf("user %d finish\n", i);
        }
    }
end:
    printf("Server will shutdown in 5 seconds.\n");
    for (int i = 5; i > 0; i--) {
        printf("%d...\n", i);
        Sleep(1000);
    }
    serverShutdown();
    return 0;
}
