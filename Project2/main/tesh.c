#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "./tesh.h"

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

/**
 * Splits the line into arguments like argv in a main function
 * char *line is a pointer to the line that has been read.
 */
char **splitLine(char *line) {

  int bufsize = TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "tesh: allocation error\n");
    exit(0);
  }

  // Create a token separating by delimiters
  token = strtok(line, TOK_DELIM);

  // Does it until there is no more arguments
  while (token != NULL) {
    tokens[position] = token;
    position++;

    // If buffer has been exceed, expands it dinamically
    if (position >= bufsize) {
      bufsize += TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "tesh: allocation error\n");
        exit(0);
      }
    }

    token = strtok(NULL, TOK_DELIM);
  }

  // A null terminated string
  tokens[position] = NULL;
  return tokens;
}

/**
 * Executes a program where there is no pipes
 * char **args is an array of pointers to null terminated strings
 */
int executeCommand(char **args) {
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child Process
    // Finds a command and executes it.
    if (strcmp(args[0], "chmod") == 0) {
      if (execv("../commands/chmod", args) == -1) {
        printf("Error con chmod!\n");
      }
    } else if (strcmp(args[0], "grep") == 0) {
      if (execv("../commands/grep", args) == -1) {
        printf("Error con grep!\n");
      }
    } else if (strcmp(args[0], "ls") == 0) {
      if (execv("../commands/ls", args) == -1) {
        printf("Error con ls!\n");
      }
    } else if (strcmp(args[0], "exit") == 0) {
      exit(0); 
    } else {
      printf("Comando no reconocido\n");
    }

    // Kills child
    exit(0);

  } else if (pid < 0) {
    printf("Error\n");
  } else {

    // Checks if exit command has been entered
    if (strcmp(args[0], "exit") == 0)
      exit(0); 
    
    // Father waits until child has ended
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

/**
 * Executes commands where there is a pipe
 */
int executeWithPipe(char **args1, char **args2) {
  
  // Creates a pipe between the processess
  int pipefd[2];
  pid_t pid1, pid2;

  if (pipe(pipefd) == -1) {
    printf("Error creando pipe\n");
  }

  pid1 = fork();
  if(pid1 < 0)
    printf("Error en fork!\n");


  if (pid1 == 0) {
    // Child Process 1
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    // Checks avalible commands
    if (strcmp(args1[0], "chmod") == 0) {
      if (execv("../commands/chmod", args1) == -1) {
        printf("Error con chmod!\n");
      }
    }
    else if (strcmp(args1[0], "ls") == 0) {
      if (execv("../commands/ls", args1) == -1) {
        printf("Error con ls!\n");
      }
    } else if (strcmp(args1[0], "grep") == 0) {
      if (execv("../commands/grep", args1) == -1) {
        printf("Error con grep!\n");
      }
    } else {
      printf("Comando no reconocido\n");
    }


    exit(0);
  } else {
    //  Waits for first command
    wait(&pid1);

    pid2 = fork();
    if(pid2 < 0)
      printf("Error en fork!\n");
    
    if (pid2 == 0) {
      // Child Process 2
      close(pipefd[1]);
      dup2(pipefd[0], STDIN_FILENO);
      close(pipefd[0]);
      
      // Checks avalibre commands
      if (strcmp(args2[0], "chmod") == 0) {
        if (execv("../commands/chmod", args2) == -1) {
          printf("Error con chmod!\n");
        }
      }
      else if (strcmp(args2[0], "ls") == 0) {
        if (execv("../commands/ls", args2) == -1) {
          printf("Error con ls!\n");
        }
      } else if (strcmp(args2[0], "grep") == 0) {
        if (execv("../commands/grep", args2) == -1) {
          printf("Error con grep!\n");
        }
      } else {
        printf("Comando no reconocido\n");
      }

      exit(0);
    } else {
      // Father wait for child to end
      wait(&pid2);
      return 1;
    }

  }

  return 1;
}

/**
 * Reads a file to execute commands
 */
int readFromFile(char *filename) {
  
  char buffer[1024];
  FILE *fp;

  // Opens the file
  fp = fopen(filename, "r");

  if (fp == NULL) {
    printf("Error abriendo el archivo.\n");
  }

  char *line;
  line = fgets(buffer, sizeof(buffer), fp);

  while (line) {
    char **args1;
    char **args2;
    char delim[2] = "|";

    char *p11;
    char *p22;
    p11 = strtok(line, delim);
    p22 = strtok(NULL, delim);

    // Checks if there is a pipe
    if (p22) {
      char *pipeInd2 = " ~"; 
      char *result2 = malloc(strlen(p11) + strlen(pipeInd2) + 1); 

      strcpy(result2, p11);
      strcat(result2, pipeInd2);

      args1 = splitLine(result2);
      args2 = splitLine(p22);

      executeWithPipe(args1, args2);
    } else {
      // If there is only a single command
      args1 = splitLine(p11);
      executeCommand(args1);
    }

    line = fgets(buffer, sizeof(buffer), fp);
  }

  return 1;
}

/**
 * Handler to not terminate with CTRL + C
 */
void sigintHandler (int sig_num) {
  printf("\nPara salir del programa ingrese exit!\n");
  return;
}

/**
 * Creates a prompt to introduce commands
 */ 
void loop(void) {
  char **args1;
  char **args2;
  char delim[2] = "|";

  do {
    // Avoid CTRL + C exits
    signal(SIGINT, sigintHandler); 

    printf("tesh >>> ");

    // Gets user input
    size_t buffsize = 1024;
    char *buffer = malloc(buffsize * sizeof(char*));
    fgets(buffer, buffsize, stdin);
    
    char *p1;
    char *p2;
    p1 = strtok(buffer, delim);
    p2 = strtok(NULL, delim);

    if (p2) {
      // If there is only one pipe
      char *pipeInd = " ~"; 
      char *result = malloc(strlen(p1) + strlen(pipeInd) + 1); 

      strcpy(result, p1);
      strcat(result, pipeInd);

      args1 = splitLine(result);
      args2 = splitLine(p2);
      executeWithPipe(args1, args2);
    } else {
      // If there is no pipe
      args1 = splitLine(p1);      
      executeCommand(args1);
    }
    
  } while (1);
}

/**
 * Main function to start selected mode
 */
int main (int argc, char *argv[]) {

  if (argc == 1) {
    loop();
  } else if (argc > 1) {
    readFromFile(argv[1]);
  }

  return 0;
}
