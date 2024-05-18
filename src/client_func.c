#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "..\header\com_setup.h"
#include "..\header\poker.h"
#pragma warning(disable:4700)
#define BUFFER_SIZE 1024
SOCKET g_sock;
int recvCard(int *client_card, char *buffer){
    int status = recv(g_sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){printf("Failed to receive card."); return 1;}
    str2int(client_card,buffer);
    memset(buffer,0,sizeof(buffer));
    return 0;
}
int chooseType(char *buffer, int *card){
    memset(buffer, 0, sizeof(buffer));
    int status = recv(g_sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){printf("Failed to receive card."); return 1;}
    int input;
    printf("\nList of Hand Types:\n");
    printf("\t1. Single\n");
    printf("\t2. Pair\n");
    printf("\t3. Straight\n");
    printf("\t4. Full House\n");
    printf("\t5. Four of a Kind\n");
    printf("\t6. Flush\n");
    printf("\t7. Skip\n");
    printf("Please choose Hand Type: ");
    choosetype:
    scanf("%d", &input);
    if(input<1||input>7){
        printf("Please check your input.\n");
        goto choosetype;
    }
    memset(buffer, 0, sizeof(buffer));
    itoa(input,buffer,10);
    status = send(g_sock, buffer, strlen(buffer),0);
    if(status==SOCKET_ERROR){
        printf("Failed to choose type.\n");
        return(1);
    }
    // switch(atoi(input)){
    //     case 1:
    //         break;
    //     case 2:
    //         break;
    //     case 3:
    //         break;
    //     case 4:
    //         break;
    //     case 5:
    //         break;
    //     case 6:
    //         break;
    //     case 7:
    //         break;
    //     default:
    //         break;
    // }
    // return 0;
}