#include <semaphore.h>
#define MAXCHAR 200

// ACTIONS definition
extern char READ[];
extern char CREATE[];
extern char SUCCESS[];
extern char CANCEL[];
extern char FAILURE[];
extern char WRITE[];
extern char INCLUSIVE[];
extern char EXCLUSIVE[];
extern char APPROVAL[];
extern char DISAPPROVAL[];
extern char* ACTIONS[];
extern int size;

double random_0_1();

int duration;

char message[MAXCHAR];
char from[MAXCHAR];


sem_t mutex; 
