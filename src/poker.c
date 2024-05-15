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
void printcard(int *card, int size){
    for(int i=0;i<size; i++){
        switch (card[i]%4)
        {
        case 0:
            if (card[i]/4+3==15){printf("Clever  2\t");}
            else if (card[i]/4+3==14) {printf("Clever  A\t");}
            else if (card[i]/4+3==11) {printf("Clever  J\t");}
            else if (card[i]/4+3==12) {printf("Clever  Q\t");}
            else if (card[i]/4+3==13) {printf("Clever  K\t");}
            else{printf("Clever %2d\t", card[i]/4+3);}
            break;
        case 1:
            if (card[i]/4+3==15){printf("Club    2\t");}
            else if (card[i]/4+3==14) {printf("Club    A\t");}
            else if (card[i]/4+3==11) {printf("Club    J\t");}
            else if (card[i]/4+3==12) {printf("Club    Q\t");}
            else if (card[i]/4+3==13) {printf("Club    K\t");}
            else{printf("Club   %2d\t", card[i]/4+3);}
            break;
        case 2:
            if (card[i]/4+3==15){printf("Heart   2\t");}
            else if (card[i]/4+3==14) {printf("Heart   A\t");}
            else if (card[i]/4+3==11) {printf("Heart   J\t");}
            else if (card[i]/4+3==12) {printf("Heart   Q\t");}
            else if (card[i]/4+3==13) {printf("Heart   K\t");}
            else{printf("Heart  %2d\t", card[i]/4+3);}
            break;
        case 3:
            if (card[i]/4+3==15){printf("Blade   2\t");}
            else if (card[i]/4+3==14) {printf("Blade   A\t");}
            else if (card[i]/4+3==11) {printf("Blade   J\t");}
            else if (card[i]/4+3==12) {printf("Blade   Q\t");}
            else if (card[i]/4+3==13) {printf("Blade   K\t");}
            else{printf("Blade  %2d\t", card[i]/4+3);}
            break;
        default:
            break;
        }
        if ((i+1)%5==0){printf("\n");}
    }
}

int main(){
    int **card;
    card = shuffle();
    printf("A:\n");
    printcard(card[0],26);
    printf("\nB\n");
    printcard(card[1],26);
}