/******************************/
/*此檔案皆為B11131016鄧盛文所寫*/
/******************************/

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "..\header\client_func.h"
#include "..\header\com_setup.h"
#include "..\header\poker.h"
SOCKET g_sock;
#define LOCALHOST "127.0.0.1"
int main(int argc, char* argv[]) {
    // Get server IP and connect to server
    char* serveraddr = LOCALHOST;
    if (argc == 2) {
        serveraddr = argv[1];
    }
    g_sock = client_setup(serveraddr);
    // Declare Variable
    int status = 0;
    char buffer[BUFFER_SIZE] = {0};
    int client_card[26];
    // Hold
    printf("Wait for other players...\n");
    // Game start
    gameStart(buffer);
    Sleep(500);
    int first = 1;
    while (1) {
        // Get the card and print it
        if (getCard(buffer, client_card)) {
            goto end;  // Break out of loop if ERROR
        }
        // Sleep(500 ms) at the first cycle
        if (first) {
            Sleep(500);
            first = 0;
        }
        // Send or ask the card type
        chooseType(buffer, client_card);
        // Check if the game is over
        status = gameOver(buffer);
        if (status) {
            // Break out of loop if the game is over
            goto end;
        }
        cls;
    }
// Shutdown the application
end:
    printf("Game is over.\n");
    printf("System will shutdown in 5 seconds.\n");
    for (int i = 5; i > 0; i--) {
        printf("%d...\n", i);
        Sleep(1000);
    }
    return 0;
}