char **splitLine(char *line);

int executeCommand(char **args);

int executeWithPipe(char **args1, char **args2);

int readFromFile(char *filename);

void sigintHandler (int sig_num);

void loop(void);
