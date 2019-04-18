#include <stdio.h>

// Manuel Faria 15-10463
// Juan Oropeza 15-11041
// Jesús Kauze 12-10273

// Processes Module

int main (int argc, char *argv[]) {
  // Header
  printf("Project 1 - Processes\n");
  printf("Manuel Faria 15-10463\nJuan Oropeza 15-11041\nJesús Kauze 12-10273\n");

  // Arguments verification
  if (argc < 3) {
    printf("Uso: ./paisProcesos <duración> [directorio]\n");
    return 0;
  } else {
    printf("Duración: %s\n", argv[1]);
    printf("Directorio: %s\n", argv[2]);
  }
  return 0;
}
