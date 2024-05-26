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
    Sleep(500);
    int first = 1;
    while(1){
        if(getCard(buffer,client_card)){
            goto end;
        }
        if(first){
            Sleep(500);
            first = 0;
        }
        chooseType(buffer,client_card);
        status = gameOver(buffer);
        if(status){
            goto end;
        }
        cls;
    }
    end:
    printf("Game is over.\n");
    printf("System will shutdown in 5 seconds.\n");
    for(int i = 5; i >0 ; i--){
        printf("%d...\n",i);
        Sleep(1000);
    }
    return 0;
}