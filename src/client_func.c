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
    int status = recvCard(client_card,buffer);
    if(status!=0){
        printf("Deal ERROR.\n");
        return -1;
    }
    printf("Your deck:\n");
    printCard(client_card,26);
    return 0;
}
int recvCard(int *client_card, char *buffer){
    clbuf;
    int status = recv(g_sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){printf("Failed to receive card."); return 1;}
    // printf("Recv card: %s\n", buffer);
    str2int(client_card,buffer);
    // if(str2int(client_card,buffer)){return 1;}
    clbuf;
    return 0;
}
int chooseType(char *buffer, int *card){
    memset(buffer, 0, sizeof(buffer));
    int status = recv(g_sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){printf("Failed to receive card."); return 1;}
    choose_restart:
    int input;
    if(buffer[0]=='@'){
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
    }
    else{
        input = atoi(&buffer[0]);
        printf("Mode is: ");
        switch(input){
            case 1:
                printf("Single\n");
                break;
            case 2:
                printf("Pair\n");
                break;
            case 3:
                printf("Straight\n");
                break;
            case 4:
                printf("Full House\n");
                break;
            case 5:
                printf("Four of a kind\n");
                break;
            case 6:
                printf("Flush\n");
                break;
        }
        printf("\n");
    }
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
            fullhouse(card, buffer);
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
    clbuf;
    status = recv(g_sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){printf("Failed to receive card."); return 1;}
    if(buffer[0]=='#'){ printf("Please choose again.\n");goto choose_restart; }
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
    int prev[5];
    char temp[5];
    clbuf;
    recv(g_sock,buffer,BUFFER_SIZE,0);
    str2int(prev,buffer);
    if(prev[4]!=-1){
        printf("Another player throw: ");
        printCard(prev,5);
    }
    single_restart:
    printf("Please choose one card: ");
    scanf("%d", &num);
    memset(buffer,0,sizeof(buffer));
    sprintf(temp, "%d", num-1);
    strcat(buffer,"-1 -1 -1 -1 ");
    strcat(buffer,temp);
    if(card[num]<prev[4]){
        printf("Cards are smaller than previous, please choose again.\n");
        goto single_restart;
    }
    int status = send(g_sock, buffer, BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){
        printf("Failed to send card.\n");
        return 1;
    }
    clbuf;
    status = recv(g_sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){
        printf("Server No Response.\n");
        return 1;
    }
    return 0;
}

int pair(int *card, char *buffer){
    int num1, num2;
    int prev[5];
    char temp[5];
    clbuf;
    recv(g_sock,buffer,BUFFER_SIZE,0);
    str2int(prev,buffer);
    if(prev[4]!=-1){
        printf("Another player throw: ");
        printCard(prev,5);
    }
    pair_restart:
    clbuf;
    printf("Please choose two card: ");
    scanf("%d %d", &num1, &num2);
    memset(buffer,0,sizeof(buffer));
    sprintf(temp, "%d %d", num1-1, num2-1);
    printf("You've chose %2d and %2d.\n", num1, num2);
    int check = card[num2-1]/4 - card[num1-1]/4;
    if(check||num2==num1){
        printf("Please choose again.\n", check);
        goto pair_restart;
    }
    if(card[num2-1]<prev[4] && card[num1-1]<prev[4]){
        printf("Cards are smaller than previous, please choose again.\n");
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
    return 0;
}
int checkfullhouse(int *num){
    if(num[0]/4!=num[1]/4){return 1;}
    if(num[3]/4!=num[4]/4){return 1;}
    if(num[2]/4==num[1]/4 || num[2]/4==num[1]/4){
        return 0;
    }
    return 1;
}
int fullhouse(int *card, char *buffer){
    int num[5];
    char temp[5];
    fullhouse_restart:
    clbuf;
    printf("Please choose two card: ");
    scanf("%d %d %d %d %d", &num[0], &num[1], &num[2], &num[3], &num[4]);
    memset(buffer,0,sizeof(buffer));
    sprintf(temp, "%d %d %d %d %d",  num[0]-1, num[1]-1, num[2]-1, num[3]-1, num[4]-1);
    Sort(num,5);
    printf("You choose %2d %2d %2d %2d and %2d.\n", num[0], num[1], num[2], num[3], num[4]);
    if(checkfullhouse(num)){
        printf("Please choose again.\n");
        goto fullhouse_restart;
    }
    strcat(buffer,temp);
    int status = send(g_sock, buffer, BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){
        printf("Failed to send card.\n");
        return 1;
    }
    clbuf;
    status = recv(g_sock,buffer,BUFFER_SIZE,0);
    if(status==SOCKET_ERROR){
        printf("Server No Response.\n");
        return 1;
    }
    if(buffer[0]!='*'){
        printf("Please choose again.\n");
        goto fullhouse_restart;
    }
    return 0;
}