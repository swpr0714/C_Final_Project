#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <winsock2.h>
/* General */
void swap(int *cardA, int *cardB){
    int temp = *cardA;
    *cardA = *cardB;
    *cardB = temp;
}
void quickSort(int *number, int left, int right) { 
    if(left < right) { 
        int s = number[(left+right)/2]; 
        int i = left - 1; 
        int j = right + 1; 
        while(1) { 
            while(number[++i] < s) ;  
            while(number[--j] > s) ;  
            if(i >= j) 
                break; 
            swap(&number[i], &number[j]); 
        } 
        quickSort(number, left, i-1);   
        quickSort(number, j+1, right); 
    } 
}

/* Client */
void printNum(int num){
    switch (num/4+3)
            {
            case 15:
                printf(" 2 |\t");
                break;
            case 14:
                printf(" A |\t");
                break;
            case 13:
                printf(" K |\t");
                break;
            case 12:
                printf(" Q |\t");
                break;
            case 11:
                printf(" J |\t");
                break;
            default:
                printf("%2d |\t", num/4+3);
                break;
            }
}
void printCard(int *card, int size){
    for(int i=0;i<size; i++){
        switch (card[i]%4)
        {
        case 0:
            printf("%2d. Clever ", i+1);
            printNum(card[i]);
            break;
        case 1:
            printf("%2d. Club   ", i+1);
            printNum(card[i]);
            break;
        case 2:
            printf("%2d. Heart  ", i+1);
            printNum(card[i]);
            break;
        case 3:
            printf("%2d. Blade  ", i+1);
            printNum(card[i]);
            break;
        case -1:
            printf("              |\t");
            break;
        default:
            break;
        }
        if ((i+1)%5==0){printf("\n");}
    }
    printf("\n");
}
int int2str(int *card, char *buf){
    memset(buf,0,sizeof(buf));
    for (int i = 0; i < 26; i++) {
        char temp[10];
        sprintf(temp, "%d", card[i]);
        strcat(buf, temp);
        if (i < 25) {
            strcat(buf, " ");
        }
    }
    return 0;
}
int str2int(int *card, char *buf){
    int i = 0;
    char *token = strtok(buf, " ");
    while (token != NULL) {
        card[i++] = atoi(token);
        token = strtok(NULL, " ");
    }
    return 0;
}

/* Server */
int **shuffle(void){
    srand(time(NULL));
    int *card = (int*)malloc(52*sizeof(int));
    int **retcard = (int**)malloc(2*sizeof(int*));
    for(int i=0;i<52;i++){
        card[i]=i;
    }
    // Fisher Yates
    for(int N = 51; N>1; N--){
        int X = rand()%N;
        swap(&card[X], &card[N]);
    }
    // Dealing
    retcard[0] = &card[0];
    retcard[1] = &card[26];

    // Sorting
    quickSort(retcard[0],0,26);
    quickSort(retcard[1],0,26);
    return retcard;
}
int findOrder(int **card, SOCKET *sock){
    int user = 0;
    // Default user 1 has clever 3
    // Check if user 2 has clever 3
    for(int i = 0; i <26; i++){
        if(card[1][i] == 0){
            user = 1;
        }
    }
    if(user){
        SOCKET socktemp = sock[0];
        sock[0] = sock[1];
        sock[1] = socktemp;
        int *cardtemp = card[0];
        card[0] = card[1];
        card[1] = cardtemp; 
    }
    return user;
}

// int main(){
//     char buf[128] = {'\0'};
//     int **card;
//     card = shuffle();
//     int client_card[26];
//     int2str(card[0],buf);
//     printf("Server: %s",buf);
//     str2int(client_card,buf);
//     printf("\nClient: ");
//     for(int j=0; j<26;j++){
//         printf("%d",client_card[j]);
//         if(j!=25){printf(" ");}
//     }
// }