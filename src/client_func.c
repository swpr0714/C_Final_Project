#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "..\header\com_setup.h"
#include "..\header\poker.h"
#pragma warning(disable:4700)
#define BUFFER_SIZE 1024
SOCKET g_sock;
int gameStart(char *buffer){
    int status = 0;
    status = recv(g_sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){printf("Failed to receive."); exit(-1);}
    cls;
    memset(buffer,0,sizeof(buffer));
    Sleep(800);
    cls;
    return 0;
}

int getCard(char *buffer, int *client_card){
    printf("Your deck:\n");
    int status = recvCard(client_card,buffer);
    if(status!=0){
        printf("Deal ERROR.\n");
        return -1;
    }
    printCard(client_card,26);
    return 0;
}
int recvCard(int *client_card, char *buffer){
    int status = recv(g_sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){printf("Failed to receive card."); return 1;}
    printf("Recv card: %s\n", buffer);
    if(str2int(client_card,buffer)){return 1;}
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
    choosetype:
    printf("Please choose Hand Type: ");
    scanf("%d", &input);
    if(input<1||input>7){
        printf("Please check your input.\n");
        goto choosetype;
    }
    memset(buffer, 0, sizeof(buffer));
    itoa(input,buffer,10);
    status = send(g_sock, buffer, BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){
        printf("Failed to choose type.\n");
        return 1;
    }
    // return 0;
    switch(input){
        case 1:
            single(card,buffer);
            break;
        case 2:
            pair(card, buffer);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        default:
            break;
    }
    return 0;
}
int clientShutdown(){
    printf("Closing...\n");
    closesocket(g_sock);
    WSACleanup();
    printf("System has shutdown.\n");
    return 0;
}
int single(int *card, char *buffer){
    int num;
    char temp[5];
    single_restart:
    printf("Please choose one card: ");
    scanf("%d", &num);
    memset(buffer,0,sizeof(buffer));
    sprintf(temp, "%d", num-1);
    strcat(buffer,"-1 -1 -1 -1 ");
    strcat(buffer,temp);
    int status = send(g_sock, buffer, BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){
        printf("Failed to send card.\n");
        return 1;
    }
    memset(buffer,0,sizeof(buffer));
    status = recv(g_sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){
        printf("Server No Response.\n");
        return 1;
    }
    if(buffer[0]!='*'){
        printf("Please choose again.\n");
        goto single_restart;
    }
    // printf("Recv\n");
    return 0;
}

int pair(int *card, char *buffer){
    int num1, num2;
    char temp[5];
    pair_restart:
    clbuf;
    printf("Please choose two card: ");
    scanf("%d %d", &num1, &num2);
    memset(buffer,0,sizeof(buffer));
    sprintf(temp, "%d %d", num1-1, num2-1);
    printf("You choose %2d and %2d.\n", num1, num2);
    if(card[num1-1]/4 != card[num2-1]/4){
        printf("Please choose again.\n");
        goto pair_restart;
    }
    strcat(buffer,"-1 -1 -1 ");
    strcat(buffer,temp);
    int status = send(g_sock, buffer, BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){
        printf("Failed to send card.\n");
        return 1;
    }
    memset(buffer,0,sizeof(buffer));
    status = recv(g_sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){
        printf("Server No Response.\n");
        return 1;
    }
    if(buffer[0]!='*'){
        printf("Please choose again.\n");
        goto pair_restart;
    }
    return 0;
}