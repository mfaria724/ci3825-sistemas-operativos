#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
  printf("cmd2 desde archivo\n");
  
  size_t buffsize = 1024;
  char *buffer = malloc(buffsize * sizeof(char*));
  fgets(buffer, buffsize, stdin);

  printf("Str: %s\n", buffer);

  return 1;
}