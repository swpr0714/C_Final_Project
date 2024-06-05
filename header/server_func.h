#pragma once
int sendCard(int **card, char *buffer, int client);
int recvType(int i, char *buffer);
int recvCard(int client, char *buffer, int **card, int *prev_card, int mode);
int checkPass(const int mode, int *prev);
int checkWin(int **card);
int serverShutdown();
int serverend(int status, char *buffer);