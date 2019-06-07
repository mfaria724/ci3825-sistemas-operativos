#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {
  // Correct Syntax
  if (argc < 3) {
    printf("Missing operands\n");
  }
  else {

    // Gets current stat for file
    struct stat fileStat;

    // User permissions
    int userRead = 0;
    int userWrite = 0;
    int userExec = 0;

    // Group permissions
    int groupRead = 0;
    int groupWrite = 0;
    int groupExec = 0;

    // Other permissions
    int otherRead = 0;
    int otherWrite = 0;
    int otherExec = 0;

    int combination;  

    FILE *out;

    //  Counts arguments that are options
    int lastFlag = 0;
    for(int z = 0; z < argc - 1; z++){
      if(argv[z][0] == '-' || argv[z][0] == '+')
        lastFlag += 1;
      if(strcmp(">",argv[z]) == 0){
          out = fopen(argv[argc - 1], "w+");
          fclose(out);
      } 
    }

    for(int z = lastFlag + 1; z <= argc - 1; z++){

      if(strcmp("<",argv[z]) == 0)
        z++;

      if(strcmp(">",argv[z]) == 0)
        break;

      if (stat(argv[z], &fileStat) < 0) {
        printf("Error getting stat for file %s\n", argv[z]);
        return 1;
      }

      // Recognize actual permissions

      // User permissions

      if (fileStat.st_mode & S_IRUSR) { userRead = 4; }
      if (fileStat.st_mode & S_IWUSR) { userWrite = 2; }
      if (fileStat.st_mode & S_IXUSR) { userExec = 1; }

      // Group permissions

      if (fileStat.st_mode & S_IRGRP) { groupRead = 4; }
      if (fileStat.st_mode & S_IWGRP) { groupWrite = 2; }
      if (fileStat.st_mode & S_IXGRP) { groupExec = 1; }

      // Other permissions

      if (fileStat.st_mode & S_IROTH) { otherRead = 4; }
      if (fileStat.st_mode & S_IWOTH) { otherWrite = 2; }
      if (fileStat.st_mode & S_IXOTH) { otherExec = 1; }


      // Iterates over provided options
      for (int z = 1; z < argc-1 ; z++) {

        combination = strlen(argv[z]);

        // Asign bits
        if (argv[z][0] == '+' && combination > 2 ) {
          char* flags = argv[z];
          int len = strlen(flags);

          for (int w = 1; w < len ; w++){
            char letter = flags[w];
            if (letter == 'r') {
              userRead = 4;
              groupRead = 4;
              otherRead = 4;
            } else if (letter == 'w') {
              userWrite = 2;
              groupWrite = 2;
              otherWrite = 2;
            } else if(letter == 'x'){
              userExec = 1;
              groupExec = 1;
              otherExec = 1;
            } else{
              printf("Unrecognized operation -%c\n", argv[z][w]);
              return 1;
            }
          }

        } else if (argv[z][0] == '-' && combination > 2 ) {
          char* flags = argv[z];
          int len = strlen(flags);

          for (int w = 1; w < len ; w++){
            char letter = flags[w];
            if (letter == 'r') {
              userRead = 0;
              groupRead = 0;
              otherRead = 0;
            } else if (letter == 'w') {
              userWrite = 0;
              groupWrite = 0;
              otherWrite = 0;
            } else if(letter == 'x'){
              userExec = 0;
              groupExec = 0;
              otherExec = 0;
            } else{
              printf("Unrecognized operation -%c\n", argv[z][w]);
              return 1;
            }
          }

        } else { 
          if (strcmp("+r", argv[z]) == 0) {
            userRead = 4;
            groupRead = 4;
            otherRead = 4;
          } else if (strcmp("-r", argv[z]) == 0) {
            userRead = 0;
            groupRead = 0;
            otherRead = 0;
          } else if (strcmp("+w", argv[z]) == 0) {
            userWrite = 2;
            groupWrite = 2;
            otherWrite = 2;
          } else if (strcmp("-w", argv[z]) == 0) {
            userWrite = 0;
            groupWrite = 0;
            otherWrite = 0;
          } else if (strcmp("+x", argv[z]) == 0) {
            userExec = 1;
            groupExec = 1;
            otherExec = 1;   
          } else if (strcmp("-x", argv[z]) == 0) {
            userExec = 0;
            groupExec = 0;
            otherExec = 0;        
          } else{
            if(argv[z][0] == '-'){
              printf("Unrecognized operation %s\n", argv[z]);
              return 1;
            }
          }
        }
      }

      // Create mode to save with chmod
      int user = userRead + userWrite + userExec;
      int group = groupRead + groupWrite + groupExec;
      int other = otherRead + otherWrite + otherExec;

      char mode[4] = "0";
      char userPerm[2] = "";
      char groupPerm[2] = "";
      char otherPerm[2] = "";

      // Convert modes in strings
      sprintf(userPerm, "%d", user);
      sprintf(groupPerm, "%d", group);
      sprintf(otherPerm, "%d", other);

      // Join modes
      strcat(mode, userPerm);
      strcat(mode, groupPerm);
      strcat(mode, otherPerm);

      // Transforms number into decimal to be used in chmod syscall 
      int i = strtol(mode, 0, 8);

      // Modifies permissions
      if (chmod(argv[z],i) < 0) {
        fprintf(stderr, "%s: error - %d (%s)\n",
        argv[0], errno, strerror(errno));
        exit(1);
      }
    }
  }

  return 0;
}