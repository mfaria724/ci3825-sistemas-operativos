#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#define MAXCHAR 200

// Project Libraries
#include "../headers/president.h"
#include "../headers/congress.h"
#include "../headers/supremeCourt.h"
#include "../headers/press.h"
#include "../headers/utils.h"

// CI3825 - Operating Systems I 
// Manuel Faria 15-10463
// Juan Oropeza 15-11041
// Jesús Kauze 12-10273
// Threads Module

// This file contains main function to execute the project implementation
// with threads using the POSIX library pthreads. 
int main (int argc, char *argv[]) {
  // Header
  printf("#### Project 1 - Threads ####\n\n");
  printf("Manuel Faria 15-10463\nJuan Oropeza 15-11041\nJesús Kauze 12-10273\n\n");

  // Arguments verification
  if (argc < 3) {
    printf("Uso: ./paisHilos <duración> [directorio]\n");
    return 0;
  } else {
    printf("Duración: %s\n", argv[1]);
    printf("Directorio: %s\n", argv[2]);

    // Threads identifiers
    pthread_t threadPresident;
    pthread_t threadCongress;
    pthread_t threadSupremeCourt;
    pthread_t threadPress;

    // Initializes semaphore
    sem_init(&mutex, 0, 1);

    // Assign default directory to read files.
    char path1[MAXCHAR] = ".";
    char path2[MAXCHAR] = "."; 
    char path3[MAXCHAR] = "."; 
    if (argc > 2) {
      strcpy(path1, argv[2]);
      strcpy(path2, argv[2]);
      strcpy(path3, argv[2]);
    }
    
    // Threads creation
    pthread_create(&threadPresident, NULL, president, strcat(path1, "/executiveBranch.acc"));
    pthread_create(&threadCongress, NULL, congress, strcat(path2, "/legislativeBranch.acc"));
    pthread_create(&threadSupremeCourt, NULL, supremeCourt, strcat(path3, "/judicialBranch.acc"));
    pthread_create(&threadPress, NULL, press, NULL);
    
    // Wait for threads to end
    pthread_join(threadPresident, NULL);    
    pthread_join(threadCongress, NULL);
    pthread_join(threadSupremeCourt, NULL);

    printf("\n¡ALDEANOS QUEMAN LA HEMEROTECA!\n");
    printf("¡REINA EL PANICO DESPUES DE LA GUERRA!\n\n");
    printf("\nEl modelo de gobierno ha fracasado. Hubo una revuelta\n");
    printf("y los pobladores decidieron quemar la hemeroteca, por lo\n");
    printf("que no queda evidencia de ninguno de los resultados generados\n");
    printf("por este algoritmo de altisima calidad. \n");
    printf("Los resultados obtenidos evidencian que el sistema de gobierno no es\n");
    printf("bueno, por lo que recomedamos al gobierno de transicion no\n");
    printf("debe seleccionar ningun sistema y vivir en anarquia.\n");

    // Destroys the semaphore
    sem_destroy(&mutex); 
  }

  return 0;
}
