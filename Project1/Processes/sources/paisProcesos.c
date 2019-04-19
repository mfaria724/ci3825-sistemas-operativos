#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../headers/president.h"
#define MAXCHAR 200

// Manuel Faria 15-10463
// Juan Oropeza 15-11041
// Jesús Kauze 12-10273

// Processes Module

int main (int argc, char *argv[]) {
  // Header
  printf("Project 1 - Processes\n");
  printf("Manuel Faria 15-10463\nJuan Oropeza 15-11041\nJesús Kauze 12-10273\n");

  // Arguments verification
  if (argc < 2) {
    printf("Uso: ./paisProcesos <duración> [directorio]\n");
    return 0;
  } else {
    printf("Duración: %s\n", argv[1]);
    printf("Directorio: %s\n", argv[2]);

    // Assign default directory to read files.
    char path[MAXCHAR] = "."; 
    if (argc > 2) {
      strcpy(path, argv[2]);
    }

    int presidentId, congressId, supremeCourtId; 
    presidentId = fork();
    
    // Creates President
    if (presidentId == 0) {
      printf("I'm the President\n");
      congressId = -1;
      supremeCourtId = -1;

      // Starts President
      president(strcat(path, "/legislativeBranch.acc"));
    } 
    else if (presidentId > 0) {
      printf("I'm paisProcesos 1\n");
      congressId = fork();
    }

    // Creates Congress
    if (congressId == 0) {
      printf("I'm the Congress\n");
      supremeCourtId = -1;
    } else if (congressId > 0) {
      printf("I'm paisProcesos 2\n");
      supremeCourtId = fork();
    }

    // Creates Supreme Court
    if (supremeCourtId == 0) {
      printf("I'm the Supreme Court\n");
    } else if (supremeCourtId > 0) {
      printf("I'm paisProcesos 3\n");
    }

  }

  return 0;
}
