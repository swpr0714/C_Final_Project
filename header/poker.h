#define cls system("cls")

void swap(int *cardA, int *cardB);
void quickSort(int* card, int left ,int right);

void printNum(int num);
void printCard(int *card, int size);
int int2str(int *card, char *buf);
int str2int(int *card, char *buf);

int **shuffle(void);
int findOrder(int **card, SOCKET *sock);
