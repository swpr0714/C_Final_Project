int gameStart(char *buffer);
int getCard(char *buffer, int *client_card);
int recvCard(int *client_card, char *buffer);
int chooseType(char *buffer, int *card);
int clientShutdown();
int single(int *card, char *buffer);
int pair(int *card, char *buffer);
int checkfullhouse(int *num);
int fullhouse(int *card, char *buffer);