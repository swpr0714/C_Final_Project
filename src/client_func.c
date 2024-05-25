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
            fullHouse(card, buffer);
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
        printf("Another player throw:\n");
        printCard(prev,5);
    }
    printf("If you want to pass you can input -3\n");
    single_restart:
    printf("Please choose one card: ");
    scanf("%d", &num);
    clbuf;
    if(num==-3){
        strcat(buffer,"-1 -1 -1 -1 -1");
        goto pass;
    }
    sprintf(temp, "%d", num-1);
    strcat(buffer,"-1 -1 -1 -1 ");
    strcat(buffer,temp);
    if(card[num-1]==-2){
        printf("Please choose again.\n");
        goto single_restart;
    }
    if(card[num-1]<prev[4]){
        printf("Cards are smaller than previous, please choose again.\n");
        goto single_restart;
    }
    pass:
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
        printf("Another player throw:\n");
        printCard(prev,5);
    }
    printf("If you want to pass you can input -3 -3\n");
    pair_restart:
    clbuf;
    printf("Please choose two card: ");
    scanf("%d %d", &num1, &num2);
    memset(buffer,0,sizeof(buffer));
    sprintf(temp, "%d %d", num1-1, num2-1);
    // printf("You've chose %2d and %2d.\n", num1, num2);
    if(num1==-3&&num2==-3){
        strcat(buffer,"-1 -1 -1 -1 -1");
        goto pass;
    }
    strcat(buffer,"-1 -1 -1 ");
    strcat(buffer,temp);
    int check = card[num2-1]/4 - card[num1-1]/4;
    if(check||num2==num1||card[num2-1]==-2||card[num1-1]==-2){
        printf("Please choose again.\n");
        goto pair_restart;
    }
    if(card[num2-1]<prev[4] && card[num1-1]<prev[4]){
        printf("Cards are smaller than previous, please choose again.\n");
        goto pair_restart;
    }
    pass:
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
int checkFullHouse(int *card, int *num, int *prev){
    for(int i=0;i<5;i++){
        for(int j=i+1;j<5;j++){
            if(num[i]==num[j]){
                return 1;
            }
        }
    }
    if(card[num[0]-1]/4!=card[num[1]-1]/4){return 1;}
    if(card[num[3]-1]/4!=card[num[4]-1]/4){return 1;}
    if((card[num[2]-1]/4==card[num[1]-1]/4 || card[num[2]-1]/4==card[num[3]-1]/4)&&card[num[2]-1]>prev[2]){
        return 0;
    }
    return 1;
}
int fullHouse(int *card, char *buffer){
    int num[5];
    char temp[5];
    int prev[5];
    clbuf;
    recv(g_sock,buffer,BUFFER_SIZE,0);
    str2int(prev,buffer);
    if(prev[4]!=-1){
        printf("Another player throw:\n");
        printCard(prev,5);
    }
    printf("If you want to pass you can input -3 -3 -3 -3 -3\n");
    fullHouse_restart:
    printf("Please choose five card in \"A A A B B\" order: ");
    scanf("%d %d %d %d %d", &num[0], &num[1], &num[2], &num[3], &num[4]);
    Sort(num,5);
    clbuf;
    if(num[0]==-3){
        strcat(buffer,"-1 -1 -1 -1 -1");
        goto pass;
    }
    for(int i=0; i<5; i++){
        itoa(num[i]-1,temp,10);
        strcat(buffer,temp);
        if(i!=4){
            strcat(buffer," ");
        }
    }
    if(checkFullHouse(card,num,prev)){
        printf("Please choose again.\n");
        goto fullHouse_restart;
    }
    pass:
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
    clbuf;
    return 0;
}

int gameOver(char *buffer){
    clbuf;
    recv(g_sock,buffer,BUFFER_SIZE,0);
    if(buffer[0]=='A'){
        printf("Player 1 Win.\n");
        printf("Game is over.\n");
        return 1;
    }
    else if(buffer[0]=='B'){
        printf("Player 2 Win.\n");
        printf("Game is over.\n");
        return 2;
    }
    else if(buffer[0]=='#'){
        // printf("Continue.\n");
        return 0;
    }
    else{
        printf("%s\n", buffer);
        return -1;
    }
}