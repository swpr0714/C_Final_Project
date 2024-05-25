int gameStart(char *buffer);
int getCard(char *buffer, int *client_card);
int recvCard(int *client_card, char *buffer);
int chooseType(char *buffer, int *card);
int clientShutdown();
int single(int *card, char *buffer);
int pair(int *card, char *buffer);
int checkFullHouse(int *num);
int fullHouse(int *card, char *buffer);