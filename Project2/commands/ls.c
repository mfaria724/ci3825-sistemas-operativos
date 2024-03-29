#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

int human_read(int a){
    return a / 1000;
}

void printFileProperties(struct stat stats, int G, int i, int h, int g, struct passwd *tf, struct group *gf, char* namefile, int pollito_mayor, FILE* out)
{
    // [Inode]
    if (i == 1 && pollito_mayor == 0) {
        printf("%-10zu ", stats.st_ino);
    } else if (i == 1 && pollito_mayor == 1) {
        char str[30];
        sprintf(str, "%zu ", stats.st_ino);
        fputs(str, out);
    }

    // [file type]
    // http://manpagesfr.free.fr/man/man2/stat.2.html
    if (pollito_mayor == 0) {
        switch (stats.st_mode & S_IFMT) {
            case S_IFBLK:  printf("b"); break; //block device
            case S_IFCHR:  printf("c"); break; //caracter device
            case S_IFDIR:  printf("d"); break; //directory 
            case S_IFIFO:  printf("p"); break; //fifo/pipe
            case S_IFLNK:  printf("l"); break; //Sym link
            case S_IFSOCK: printf("s"); break; //socket
            default:       printf("-"); break; //unasigned
        }
    } else {
        switch (stats.st_mode & S_IFMT) {
            case S_IFBLK:  fputs("b", out); break; //block device
            case S_IFCHR:  fputs("c", out); break; //caracter device
            case S_IFDIR:  fputs("d", out); break; //directory 
            case S_IFIFO:  fputs("p", out); break; //fifo/pipe
            case S_IFLNK:  fputs("l", out); break; //Sym link
            case S_IFSOCK: fputs("s", out); break; //socket
            default:       fputs("-", out); break; //unasigned
        }
    }
    // [permissions]
    // http://linux.die.net/man/2/chmod 
    if (pollito_mayor == 0) {
        printf( (stats.st_mode & S_IRUSR) ? "r" : "-"); //
        printf( (stats.st_mode & S_IWUSR) ? "w" : "-"); // OWNER
        printf( (stats.st_mode & S_IXUSR) ? "x" : "-"); //
        printf( (stats.st_mode & S_IRGRP) ? "r" : "-");   // 
        printf( (stats.st_mode & S_IWGRP) ? "w" : "-");   // GROUP
        printf( (stats.st_mode & S_IXGRP) ? "x" : "-");   //
        printf( (stats.st_mode & S_IROTH) ? "r" : "-");     // 
        printf( (stats.st_mode & S_IWOTH) ? "w" : "-");     // OTHER
        printf( (stats.st_mode & S_IXOTH) ? "x" : "-");     //
    } else {
        fputs( (stats.st_mode & S_IRUSR) ? "r" : "-", out); //
        fputs( (stats.st_mode & S_IWUSR) ? "w" : "-", out); // OWNER
        fputs( (stats.st_mode & S_IXUSR) ? "x" : "-", out); //
        fputs( (stats.st_mode & S_IRGRP) ? "r" : "-", out);   // 
        fputs( (stats.st_mode & S_IWGRP) ? "w" : "-", out);   // GROUP
        fputs( (stats.st_mode & S_IXGRP) ? "x" : "-", out);   //
        fputs( (stats.st_mode & S_IROTH) ? "r" : "-", out);     // 
        fputs( (stats.st_mode & S_IWOTH) ? "w" : "-", out);     // OTHER
        fputs( (stats.st_mode & S_IXOTH) ? "x" : "-", out);     //   
    }
    // [number of hard links] 
    // http://www.gnu.org/software/libc/manual/html_node/Attribute-Meanings.html
    if (pollito_mayor == 0) {
        printf(" %zu ", stats.st_nlink);
    } else {
        char str[30];
        sprintf(str, " %zu ", stats.st_ino);
        fputs(str, out);
    }

    // [owner]
    // http://linux.die.net/man/3/getpwuid
    if (G != 1 && pollito_mayor == 0) {
        tf = getpwuid(stats.st_uid);
        printf("%s ", tf->pw_name);
    } else if (G != 1 && pollito_mayor == 1) {
        tf = getpwuid(stats.st_uid);
        fputs(tf->pw_name,out);
        fputs(" ",out);
    }
    
    // [group]
    // http://linux.die.net/man/3/getgrgid
    if ( g != 1 && pollito_mayor == 0 ) {
        gf = getgrgid(stats.st_gid);
        printf("%s ", gf->gr_name);
    } else if ( g != 1 && pollito_mayor == 1 ) {
        gf = getgrgid(stats.st_gid);
        fputs(gf->gr_name,out);
        fputs(" ",out);
    }

    // [size in bytes/Kbytes/Mbytes] 
    if ( h != 1 && pollito_mayor == 0 ) {
        printf("%7zu ",stats.st_size); // BYTES,         
    } else if ( h != 1 && pollito_mayor == 1 ) {
        char str[30];
        sprintf(str, "%zu ", stats.st_size);
        fputs(str, out);
    } else if ( h == 1 && pollito_mayor == 0 ) {
        if (human_read(stats.st_size) == 0) {
            printf("%8zu ",stats.st_size);
        } else if (human_read(stats.st_size) < 800) {
            printf("%7dK ",human_read(stats.st_size)); // KBYTES,                                     
        } else {
            printf("%7dM ",human_read(stats.st_size)); // MBYTES,                     
        }
    } else {
        if (human_read(stats.st_size) == 0) {
            char str[30];
            sprintf(str, "%zu ", stats.st_size);
            fputs(str, out);               
        } else if (human_read(stats.st_size) < 800) {
            char str[30];
            sprintf(str, "%dK ", human_read(stats.st_size));
            fputs(str, out);
        } else {
            char str[30];
            sprintf(str, "%dM ", human_read(stats.st_size));
            fputs(str, out);                   
        }
    }

        // [time of last modification] 
        if (pollito_mayor == 1) {
            fprintf(out,"%.12s ",ctime(&stats.st_mtime)+4);
        } else {
            printf("%.12s ", ctime(&stats.st_mtime)+4);
        } 

    // [filename]
    if (pollito_mayor == 1) {
        fprintf(out,"%s\n ",namefile);
    } else {
        printf("%s\n", namefile);
    }

}

int main(int argc, char* argv[])                                                    
{
    FILE* out;
    int final = 0;
    int only_ls = 0;
    char* base;

        //Defining Struct file for every file (called in loop)
        //Defining Struct Directory (contains the path)
    if(argc == 2 && strcmp("~",argv[argc-1]) == 0) {
        
        only_ls = 1;
        final = 1;
    } else if (argc < 2) {
        only_ls = 1;
    }
    

    DIR *thedirectory;
    struct dirent *thefile;
    struct stat thestat;

        //used to determine the file owner / group
    struct passwd *tf; 
    struct group *gf;

        // Var Used to flags
    char buf[512];
    char *flag = argv[2];
    int G = 0;
    int g = 0;
    int h = 0;
    int i = 0;
    int R = 0;
    int R2 = 0;
    int last_directory = 0;
    int counter = 0;
    int next = 0;
    int combination = 0;
    int pollito_mayor = 0;
    int pwdc = 0;
    int c_re = 1;

        // Open the directory / File (only_ls == 1 is to ./ls only)
    if (only_ls == 0) {
        for (int r = 1; r <= argc-1; r++) {
            if (strcmp(">", argv[r]) == 0) {
                out = fopen(argv[argc-1],"w+");
                pollito_mayor = 1;
                c_re = 3;
                break;
            } else {
                c_re = 1;

            }
        }
        if (strcmp("~",argv[argc-1]) == 0) {
            final = 1;
            c_re++;
        }
        thedirectory = opendir(argv[argc-c_re]);
        base = argv[argc-c_re];
    } else {
        if (strcmp("~",argv[argc-1]) == 0) {
            final = 1;
            c_re++;
        }
        thedirectory = opendir(".");
        strcpy(base,"./");

    }
        // Reading the flags
    for (int z = 1; z < argc-c_re ; z++) {
      combination = strlen(argv[z]);
      char* actual = argv[z];
      char sig = actual[0];
      if (  combination > 2 && sig == '-') {
        char* flags = argv[z];
        int len = strlen(flags);
        for (int w = 1; w < len ; w++){
            char letter = flags[w];
            if (letter == 'G') {
                G = 1;
            } else if (letter == 'g') {
                g = 1;
            } else if (letter == 'h') {
                h = 1;
            } else if (letter == 'i') {
                i = 1;
            } else if (letter == 'R') {
                R = 1;
                R2 = 1;
            } else {
                printf("Unrecognized3 operation\n");
                printf("EndOfPipe\n");
            }
        }

      } else if( sig == '-') { 
        if (strcmp("-G", argv[z]) == 0) {
            G = 1;
        } else if (strcmp("-g", argv[z]) == 0) {
            g = 1;
        } else if (strcmp("-h", argv[z]) == 0) {
            h = 1;
        } else if (strcmp("-i", argv[z]) == 0) {
            i = 1;
        } else if (strcmp("-R", argv[z]) == 0) {
            R = 1;
            R2 = 1;
        } else {
            printf("Unrecognized4 operation\n");
            printf("EndOfPipe\n");
            exit(0);
        }
      }
    }
        // its a FIle NOT directory (or current directory)
    if ( thedirectory == NULL ) {
        int y = c_re;
        char* current = argv[argc-y];
        char letter = current[0];
        // If last parameters is not a flag
        
        if (stat(argv[argc-c_re], &thestat) == 0) {
            while (stat(argv[argc-y], &thestat) == 0) {
                printFileProperties(thestat, G, i, h, g, tf, gf, argv[argc-y], pollito_mayor, out);
                y++;
            }
            if (final) {
                printf("EndOfPipe\n");
            }
            return 0;
        } else if (letter == '-') {
            // Get current directory
            thedirectory = opendir(".");
            pwdc = 1;
            strcpy(base,"./");

            
            // Get Last Flag
            combination = strlen(current);
            if (  combination > 2 ) {
                int len = strlen(current);
                for (int w = 1; w < len ; w++){
                    char letter = current[w];
                    if (letter == 'G') {
                        G = 1;
                    } else if (letter == 'g') {
                        g = 1;
                    } else if (letter == 'h') {
                        h = 1;
                    } else if (letter == 'i') {
                        i = 1;
                    } else if (letter == 'R') {
                        R = 1;
                        R2 = 1;
                    } else {
                        printf("Unrecognized operation\n");
                        printf("EndOfPipe\n");
                        exit(0);
                    }
                }

            } else { 
                if (strcmp("-G", current) == 0) {
                    G = 1;
                } else if (strcmp("-g", current) == 0) {
                    g = 1;
                } else if (strcmp("-h", current) == 0) {
                    h = 1;
                } else if (strcmp("-i", current) == 0) {
                    i = 1;
                } else if (strcmp("-R", current) == 0) {
                    R = 1;
                    R2 = 1;
                } else {
                    printf("Unrcognized operation\n");
                    printf("EndOfPipe\n");
                    exit(0);
                }
            }

        } else {
            printf("ls: no se puede acceder a '%s': No existe el directorio o archivo",argv[argc-c_re]);
            exit(1);
        }
    }

        // Used to -R. save all directory files.
    char *arr[500000] = {};
    char **ptr = arr; 

        // Main Reading files loop
    while((thefile = readdir(thedirectory)) != NULL || R2 == 1) {   

        // If -R is actived and has some directory
        if (thefile == NULL) {
            last_directory = 1; 
            if (ptr[next] != NULL) {
                char* var_dir = arr[next];
                if (strcmp(base,".") == 0){
                    strcpy(base,"./");
                }
                strcat(base,var_dir);
                printf("\n%s\n",base);
                thedirectory = opendir(base);
                thefile = readdir(thedirectory);
                next++;
            } else {
                break;
            }
        }
        
        // Used to get all Directory to -R
        int directory = 0;

        // Used to get owner and group
        if (pwdc == 0 && only_ls == 0) {
            sprintf(buf, "%s/%s", argv[argc-c_re], thefile->d_name);
        } else if (only_ls == 1) {
            sprintf(buf, "%s/%s", ".", thefile->d_name);
        } else
        {
            sprintf(buf, "%s/%s", ".", thefile->d_name);
        }
        
        
        stat(buf, &thestat);

        // Order printf 
        // [Inode]* [file type] [permissions] [number of hard links] [owner]* [group]* [size in bytes]* [time of last modification] [filename]
        
        // [Inode]
        if (i == 1 && pollito_mayor == 0) {
            printf("%-10zu ", thestat.st_ino);
        } else if (i == 1 && pollito_mayor == 1) {
            char str[30];
            sprintf(str, "%zu ", thestat.st_ino);
            fputs(str, out);
        }
        
        // [file type]
        // http://manpagesfr.free.fr/man/man2/stat.2.html
        if (pollito_mayor == 0) {
            switch (thestat.st_mode & S_IFMT) {
                case S_IFBLK:  printf("b"); break; //block device
                case S_IFCHR:  printf("c"); break; //caracter device
                case S_IFDIR:  printf("d"); directory = 1; break; //directory 
                case S_IFIFO:  printf("p"); break; //fifo/pipe
                case S_IFLNK:  printf("l"); break; //Sym link
                case S_IFSOCK: printf("s"); break; //socket
                default:       printf("-"); break; //unasigned
            }
        } else {
            switch (thestat.st_mode & S_IFMT) {
                case S_IFBLK:  fputs("b", out); break; //block device
                case S_IFCHR:  fputs("c", out); break; //caracter device
                case S_IFDIR:  fputs("d", out); directory = 1; break; //directory 
                case S_IFIFO:  fputs("p", out); break; //fifo/pipe
                case S_IFLNK:  fputs("l", out); break; //Sym link
                case S_IFSOCK: fputs("s", out); break; //socket
                default:       fputs("-", out); break; //unasigned
            }
        }

        // [permissions]
        // http://linux.die.net/man/2/chmod 
        if (pollito_mayor == 0) {
            printf( (thestat.st_mode & S_IRUSR) ? "r" : "-"); //
            printf( (thestat.st_mode & S_IWUSR) ? "w" : "-"); // OWNER
            printf( (thestat.st_mode & S_IXUSR) ? "x" : "-"); //
            printf( (thestat.st_mode & S_IRGRP) ? "r" : "-");   // 
            printf( (thestat.st_mode & S_IWGRP) ? "w" : "-");   // GROUP
            printf( (thestat.st_mode & S_IXGRP) ? "x" : "-");   //
            printf( (thestat.st_mode & S_IROTH) ? "r" : "-");     // 
            printf( (thestat.st_mode & S_IWOTH) ? "w" : "-");     // OTHER
            printf( (thestat.st_mode & S_IXOTH) ? "x" : "-");     //
        } else {
            fputs( (thestat.st_mode & S_IRUSR) ? "r" : "-", out); //
            fputs( (thestat.st_mode & S_IWUSR) ? "w" : "-", out); // OWNER
            fputs( (thestat.st_mode & S_IXUSR) ? "x" : "-", out); //
            fputs( (thestat.st_mode & S_IRGRP) ? "r" : "-", out);   // 
            fputs( (thestat.st_mode & S_IWGRP) ? "w" : "-", out);   // GROUP
            fputs( (thestat.st_mode & S_IXGRP) ? "x" : "-", out);   //
            fputs( (thestat.st_mode & S_IROTH) ? "r" : "-", out);     // 
            fputs( (thestat.st_mode & S_IWOTH) ? "w" : "-", out);     // OTHER
            fputs( (thestat.st_mode & S_IXOTH) ? "x" : "-", out);     //   
        }
        
        

        // [number of hard links] 
        // http://www.gnu.org/software/libc/manual/html_node/Attribute-Meanings.html
        if (pollito_mayor == 0) {
            printf(" %zu ", thestat.st_nlink);
        } else {
            char str[30];
            sprintf(str, " %zu ", thestat.st_ino);
            fputs(str, out);
        }

        // [owner]
        // http://linux.die.net/man/3/getpwuid
        if (G != 1 && pollito_mayor == 0) {
            tf = getpwuid(thestat.st_uid);
            printf("%s ", tf->pw_name);
        } else if (G != 1 && pollito_mayor == 1) {
            tf = getpwuid(thestat.st_uid);
            fputs(tf->pw_name,out);
            fputs(" ",out);
        }
        
        // [group]
        // http://linux.die.net/man/3/getgrgid
        if ( g != 1 && pollito_mayor == 0 ) {
            gf = getgrgid(thestat.st_gid);
            printf("%s ", gf->gr_name);
        } else if ( g != 1 && pollito_mayor == 1 ) {
            gf = getgrgid(thestat.st_gid);
            fputs(gf->gr_name,out);
            fputs(" ",out);
        }

        // [size in bytes/Kbytes/Mbytes] 
        if ( h != 1 && pollito_mayor == 0 ) {
            printf("%7zu ",thestat.st_size); // BYTES,         
        } else if ( h != 1 && pollito_mayor == 1 ) {
            char str[30];
            sprintf(str, "%zu ", thestat.st_size);
            fputs(str, out);
        } else if ( h == 1 && pollito_mayor == 0 ) {
            if (human_read(thestat.st_size) == 0) {
                printf("%8zu ",thestat.st_size);
            } else if (human_read(thestat.st_size) < 800) {
                printf("%7dK ",human_read(thestat.st_size)); // KBYTES,                                     
            } else {
                printf("%7dM ",human_read(thestat.st_size)); // MBYTES,                     
            }
        } else {
            if (human_read(thestat.st_size) == 0) {
                char str[30];
                sprintf(str, "%zu ", thestat.st_size);
                fputs(str, out);               
            } else if (human_read(thestat.st_size) < 800) {
                char str[30];
                sprintf(str, "%dK ", human_read(thestat.st_size));
                fputs(str, out);
            } else {
                char str[30];
                sprintf(str, "%dM ", human_read(thestat.st_size));
                fputs(str, out);                   
            }

        }
        // [time of last modification] 
        if (pollito_mayor == 1) {
            fprintf(out,"%.12s ",ctime(&thestat.st_mtime)+4);
        } else {
            printf("%.12s ", ctime(&thestat.st_mtime)+4);
        }

        if (R == 1 && directory == 1 && last_directory == 0 ) {
            if (strcmp("..", thefile->d_name ) == 0 || strcmp(".", thefile->d_name ) == 0) {
            } else {
                ptr[counter] = thefile->d_name;
                counter++;
            }
        }

        // [filename]
        if (pollito_mayor == 1) {
            fprintf(out,"%s\n ",thefile->d_name);
        } else {
            printf("%s\n", thefile->d_name);
        }
        
    }

    if (final) {
        printf("EndOfPipe\n");
    }
    

    closedir(thedirectory);
}

