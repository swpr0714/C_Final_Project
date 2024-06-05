#pragma once
typedef struct {
    int rank;  // 數值3~2
    int suit;  // 花色 梅花 方塊 紅心 黑桃
} Card;
int gameStart(char *buffer);
int getCard(char *buffer, int *client_card);
int recvCard(int *client_card, char *buffer);
int chooseType(char *buffer, int *card);
int single(int *card, char *buffer);
int pair(int *card, char *buffer);
int checkStraight(int *card, int *num, int *prev);
int straight(int *card, char *buffer);
Card intToCard(int cardNum);
void convertHand(int* hand, Card* cvrtHand, int handSize);
int checkFullHouse(int *card, int *num, int *prev);
int fullHouse(int *card, char *buffer);
int checkfourOfAKind(int *card, int *num, int *prev);
int fourOfAKind(int *card, char *buffer);
int checkFlush(int *card, int *num, int *prev);
int flush(int *card, char *buffer);
int gameOver(char *buffer);
int clientShutdown();