#include "../headers/supremeCourt.h"
#include <stdio.h>
#include <string.h>
#include "../headers/utils.h"
#define MAXCHAR 200

// CI3825 - Operating Systems I 
// Manuel Faria 15-10463
// Juan Oropeza 15-11041
// Jesús Kauze 12-10273
// Supreme Court Methods

// In this file we developed all congress functions to 
// execute its decisions. 
void *supremeCourt (void* filename) {
  printf("Supreme Court from File! %s\n", (char*)filename);
  // Initialize variables
  FILE *fp;
  char line[MAXCHAR];

  // Opens file
  fp = fopen(filename, "r");

  // Checks that file could be opened
  if (fp == NULL) {
    printf("No se pudo abrir el archivo %s. Verifique que la ruta al archivo sea correcta.\n", (char *)filename);
    return NULL;
  }

  // Iterate over file's lines
  int k = 0;
  while (fgets(line, MAXCHAR, fp) != NULL) {

    char subString[MAXCHAR] = "";
    k = 0;
    // Iterate over line's characters
    for (int i = 0; i < MAXCHAR; i++) {
      subString[i] = line[i];
      
      // If has ACTION length
      if (i == (strlen(ACTIONS[k]) - 1)) {
        int result = strcmp(subString, ACTIONS[k]);

        // If matches ACTION
        if (result == 0) {
          double varRandom = random_0_1();

          if (k == 2) {
            if (varRandom > 0.5) {
              sem_wait(&mutex);
              strcpy(message, line);
              strcpy(from, "Tribunal Supremo");
              sem_post(&mutex);
            } else {
              sem_wait(&mutex);
              fgets(line, MAXCHAR, fp);
              strcpy(message, line);
              strcpy(from, "Tribunal Supremo");
              sem_post(&mutex);
            }
          }

          i = MAXCHAR;
        } else {
          // If there are more actions
          if (size/sizeof(ACTIONS[0]) > k + 1) { 
            // If next action has the same length as previous
            if (strlen(ACTIONS[k]) == strlen(ACTIONS[k+1])) { i--; }
            k++; 
          }
        }
      }
    
    } 

  }

  // Closes file 
  fclose(fp);
  return NULL;
}
