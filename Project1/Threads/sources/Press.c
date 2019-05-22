#include "../headers/press.h"
#include <stdio.h>
#include <semaphore.h>
#include "../headers/utils.h"

// CI3825 - Operating Systems I 
// Manuel Faria 15-10463
// Juan Oropeza 15-11041
// Jesús Kauze 12-10273
// Press Methods

// In this file we developed all press functions to 
// execute its decisions. 
void *press () {

  while(1) {
    sem_wait(&mutex);
    if (message[0]) {
      printf("%d. %s %s\n", duration, from, message);
      message[0] = '\0';
      from[0] = '\0';
      duration++;
    }
    sem_post(&mutex);
  }

  return NULL;
}
