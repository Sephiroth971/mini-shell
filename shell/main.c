#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char **tokenize(char *line, char **argvs){
    char *token = strtok(line," \t");
    int i=0;
    while(token){
        argvs[i++] = token;
        token = strtok(NULL," \t");
    }
    argvs[i] =NULL;
    return argvs;
}
void read_line(char *line){
    fgets(line,256,stdin);
    size_t len = strlen(line);
    if (line[len - 1]=='\n'){
        line[len - 1]='\0';
    }
}
void execute(char **argvs){
    pid_t pid = fork();

    if (pid == 0){ // child process
        printf("%s","execute in child");
        execvp(argvs[0],argvs);
        perror("execpv");
    }
    else if (pid > 0){ //parent process
        wait(NULL);
    }
    else {
        perror("fork");
    }
}
int gestion_exit(char **argvs){
    if(argvs[0] == NULL ){
        printf("%s","exit mini-shell");
        return 1;
    }
    else if (strcmp(argvs[0],"exit") == 0){
        return 0;
    }
    return 1;
}
char *getcwd(char *buf, size_t size);

int main(){
    while(1){
    char cwd[1024];
    char line[256];
    char *argvs[20];
    getcwd(cwd, sizeof(cwd));
    printf("%s >>",cwd);
    read_line(line);
    tokenize(line,argvs);

    if(!gestion_exit(argvs))
        break;
    if(strcmp(argvs[0],"cd") == 0){
    chdir(argvs[1]);
    continue;
    }
    execute(argvs);

    }
}