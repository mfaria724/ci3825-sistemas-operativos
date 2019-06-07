#include <stdio.h>

int main (int argc, char *argv[]) {
  printf("desde archivo cmd1 \n");  
  printf("argc %d\n", argc);
  printf("argv %s\n", argv[argc - 1]);
  return 1;
}
