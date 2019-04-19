#include <stdio.h>
#include "../headers/president.h"
#include <string.h>
#define MAXCHAR 200

// ACTIONS definition
const char READ[] = "leer";
const char CREATE[] = "crear:";
const char SUCCESS[] = "exito:";
const char CANCEL[] = "anular:";
const char FAILURE[] = "fracaso:";
const char WRITE[] = "escribir:";
const char INCLUSIVE[] = "inclusivo:";
const char EXCLUSIVE[] = "exclusivo:";
const char APPROVAL[] = "aprobacion:";
const char DISAPPROVAL[] = "reprobacion:";
const char* ACTIONS[] = { READ, CREATE, SUCCESS, CANCEL, FAILURE, WRITE, INCLUSIVE, EXCLUSIVE, APPROVAL, DISAPPROVAL };

int president (char* filename) {
  // Initialize variables
  FILE *fp;
  char line[MAXCHAR];

  // Opens file
  fp = fopen(filename, "r");

  // Checks that file could be opened
  if (fp == NULL) {
    printf("No se pudo abrir el archivo %s. Verifique que la ruta al archivo sea correcta.\n", filename);
    return 1;
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
          printf("\n***************** %s ENCONTRADO! *****************\n\n", ACTIONS[k]);
          i = MAXCHAR;
        } else {
          // If there are more actions
          if (sizeof(ACTIONS)/sizeof(ACTIONS[0]) > k + 1) { 
            // If next action has the same length as previous
            if (strlen(ACTIONS[k]) == strlen(ACTIONS[k+1])) { i--; }
            k++; 
          }
        }
      }
    
    } 

    printf("%s", line);

  }

  // Closes file 
  fclose(fp);
  return 0;
}