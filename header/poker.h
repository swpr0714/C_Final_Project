#pragma once
#define cls system("cls")

void swap(int *cardA, int *cardB);
void Sort(int *arr, int size);

void printNum(int num);
void printCard(int *card, int size);
int int2str(int *card, char *buf);
int str2int(int *card, char *buf);

int **shuffle(void);
int findOrder(int **card, SOCKET *sock);
