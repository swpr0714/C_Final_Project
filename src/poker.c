#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
void printNum(int num){
    switch (num/4+3)
            {
            case 15:
                printf("2\t");
                break;
            case 14:
                printf("A\t");
                break;
            case 13:
                printf("K\t");
                break;
            case 12:
                printf("Q\t");
                break;
            case 11:
                printf("J\t");
                break;
            default:
                printf("%d\t", num/4+3);
                break;
            }
}
void printCard(int *card, int size){
    for(int i=0;i<size; i++){
        switch (card[i]%4)
        {
        case 0:
            printf("Clever  ");
            printNum(card[i]);
            break;
        case 1:
            printf("Club    ");
            printNum(card[i]);
            break;
        case 2:
            printf("Heart   ");
            printNum(card[i]);
            break;
        case 3:
            printf("Blade   ");
            printNum(card[i]);
            break;
        default:
            break;
        }
        if ((i+1)%5==0){printf("\n");}
    }
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