int gameStart(char *buffer);
int getCard(char *buffer, int *client_card);
int recvCard(int *client_card, char *buffer);
int chooseType(char *buffer, int *card);
int clientShutdown();