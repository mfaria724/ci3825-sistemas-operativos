#define _GNU_SOURCE
#include<stdio.h>
#include<string.h> 

void main(int argc, char *argv[]){

  char temp[1024];
  int options[3] = {0,0,0};
  int combination;


  FILE *fp;
  FILE *out;


  if(argc > 1){

    // Reading flags
    for (int z = 1; z < argc-1 ; z++) {

      combination = strlen(argv[z]);

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

      while(fgets(temp,1000,stdin)){

        if(strcmp(temp,"EndOfPipe\n") == 0)
          break;
        
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
        
      // Counts arguments that are flags
      int lastFlag = 0;
      for(int i = 0; i < argc - 1; i++){

        if(argv[i][0] == '-')
          lastFlag += 1;

        if(strcmp(">",argv[i]) == 0){
          options[2] = 1;
          out = fopen(argv[argc - 1], "w+");
        }
      }


      for(int i = lastFlag + 2; i <= argc - 1; i++){

        // Jump to next iteration if has <
        if(strcmp("<",argv[i]) == 0)
          i++;
          
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
        fclose(fp);
               
      }
      if(options[2])
        fclose(out);
    }
  } else{
    printf("Usage: grep [OPTION]... PATTERN [FILE]...");
  }
}
