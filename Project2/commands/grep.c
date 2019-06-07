#define _GNU_SOURCE
#include<stdio.h>
#include<string.h> 

void main(int argc, char *argv[]){

  // Initializes variables
  char temp[1024];          // Buffer
  int options[3] = {0,0,0};     // Checks every option
  int combination;     // Used to get options from flags

  // Initialize I/O files
  FILE *fp;
  FILE *out;


  if(argc > 1){

    // Iterates over the arguments
    for (int z = 1; z < argc-1 ; z++) {

      combination = strlen(argv[z]);

      // If the argument is a flag, and has more than one option, iterates over it to get every option on it
      if (argv[z][0] == '-' && combination > 2 ) {

        char* flags = argv[z];
        int len = strlen(flags);

        for (int w = 1; w < len ; w++){

          char letter = flags[w];

          if (letter == 'i') {
            options[0] = 1;
          } else if (letter == 'v') {
            options[1] = 1;
          } else {
            printf("Unrecognized operation -%c\n",argv[z][w]);
            return;
          }
       } 
      // If the argument has only one option, checks what option is it
      } else { 
        if (strcmp("-i", argv[z]) == 0) {
          options[0] = 1;

        } else if (strcmp("-v", argv[z]) == 0) {
          options[1] = 1;

        } else {

          if(argv[z][0] == '-'){
            printf("Unrecognized operation %s\n",argv[z]);
            return;
          }
        }
      }
    }

    // Case Prompt
    if(argv[argc - 2][0] == '-' || argc == 2){

      // Gets input from the user until he cancels it
      while(fgets(temp,1000,stdin)){
        
        // Condition to stop the cycle if the input if coming from another command
        if(strcmp(temp,"EndOfPipe\n") == 0)
          break;
        
        // Verifies what option has to apply, then checks if the input matchs with the pattern to print it
        if(options[1]){
          if(options[0]){
            if(!strcasestr(temp,argv[argc - 1]))
              printf("%s",temp);
          } else{
            if(!strstr(temp,argv[argc - 1]))
              printf("%s",temp);    
            }
        } else{
          if(options[0]){
            if(strcasestr(temp,argv[argc - 1]))
              printf("%s",temp);
          } else{
            if(strstr(temp,argv[argc - 1]))
              printf("%s",temp);
          }
        }
      }

    // Case File    
    } else if(argv[argc - 2][0] != '-') {
        
      // Counts arguments that are flags and verifies if the output will be redirectioned to a file
      int lastFlag = 0;
      for(int i = 0; i < argc - 1; i++){

        if(argv[i][0] == '-')
          lastFlag += 1;

        if(strcmp(">",argv[i]) == 0){
          options[2] = 1;
          out = fopen(argv[argc - 1], "w+");
        }
      }

      // Iterates over every file in the input to run grep on them
      for(int i = lastFlag + 2; i <= argc - 1; i++){

        // Jump to next iteration if has <
        if(strcmp("<",argv[i]) == 0)
          i++;

        // Checks when to finish the cycle if the output is going to be redirectioned 
        if(strcmp(">",argv[i]) == 0)
          break;
            
        // Opens file
        fp=fopen(argv[i],"r");

        // Checks that file could be opened
        if (fp == NULL) {
          printf("grep: %s: No such file or directory\n", (char *)argv[i]);
        }

        // Get next line of the file
        while(fgets(temp,1000,fp)){
                    
          // If the pattern has ocurrence in the line, prints it
          if(options[1]){
            if(options[0]){
              if(!strcasestr(temp,argv[lastFlag + 1])){
                if(options[2]){
                  fputs(temp,out);
                } else {
                  printf("%s",temp);
                }
              }
            } else{
              if(!strstr(temp,argv[lastFlag + 1])){
                if(options[2]){
                  fputs(temp,out);                                    
                } else {
                  printf("%s",temp);
                }   
              }
            }
          } else{
            if(options[0]){
              if(strcasestr(temp,argv[lastFlag + 1])){
                if(options[2]){
                  fputs(temp,out);                                    
                } else {
                  printf("%s",temp);
                }
              }
            } else{
              if(strstr(temp,argv[lastFlag + 1])){
                if(options[2]){
                  fputs(temp,out);
                } else {
                  printf("%s",temp);
                }
              }  
            }
          }
        }
        // Closes input file
        fclose(fp);
               
      }
      // Closes output file
      if(options[2])
        fclose(out);
    }
  } else{
    printf("Usage: grep [OPTION]... PATTERN [FILE]...");
  }
}
