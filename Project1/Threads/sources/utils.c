#include "../headers/utils.h"
#include <stdlib.h>
#define MAXCHAR 200

// ACTIONS definition
char READ[] = "leer";
char CREATE[] = "crear:";
char SUCCESS[] = "exito:";
char CANCEL[] = "anular:";
char FAILURE[] = "fracaso:";
char WRITE[] = "escribir:";
char INCLUSIVE[] = "inclusivo:";
char EXCLUSIVE[] = "exclusivo:";
char APPROVAL[] = "aprobacion:";
char DISAPPROVAL[] = "reprobacion:";
char* ACTIONS[] = { READ, CREATE, SUCCESS, CANCEL, FAILURE, WRITE, INCLUSIVE, EXCLUSIVE, APPROVAL, DISAPPROVAL };

int size = sizeof(ACTIONS);

int duration = 1;

sem_t mutex; 

char message[MAXCHAR] = "";
char from[MAXCHAR] = "";


double random_0_1(){
  return rand() / ((double)RAND_MAX);
}