#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include "..\header\com_setup.h"
#include "..\header\poker.h"
#include "..\header\client_func.h"
SOCKET g_sock;
#define LOCALHOST "127.0.0.1"
int main(int argc, char *argv[]){
    // Connect to server
    char *serveraddr = LOCALHOST;
    if(argc==2){
        serveraddr = argv[1];
    }
    g_sock = client_setup(serveraddr);  
    //Declare Variable
    int status = 0; 
    char buffer[BUFFER_SIZE] = {0};
    int client_card[26];
    // Wait for dealing
    printf("Wait for other players...\n");
    // Game start
    gameStart(buffer);
    Sleep(2000);
    while(1){
        getCard(buffer,client_card);
        chooseType(buffer,client_card);
        status = gameOver(buffer);
        if(status){
            goto end;
        }
        cls;
    }
    printf("You have lost.\nGame over.\n");
    end:
    clientShutdown();
    cls;
    return 0;
}