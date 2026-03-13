#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_HISTORY 100

char history[MAX_HISTORY][256];
int history_count=0;


char **tokenize(char *line, char **argvs){ // tokenization
    char *token = strtok(line," \t");
    int i=0;
    while(token){
        argvs[i++] = token;
        token = strtok(NULL," \t");
    }
    argvs[i] =NULL;
    return argvs;
}

void read_line(char *line){ // readline
    fgets(line,256,stdin);
    size_t len = strlen(line);
    if (line[len - 1]=='\n'){
        line[len - 1]='\0';
    }
}

void execute(char **argvs){ // execute cmd exep : cd 
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
void cd_execute(char **argvs){
    if(argvs[1] == NULL){
        printf("cd : missing argument\n");
    }
    else {
        chdir(argvs[1]);
    }

}
int gestion_exit(char **argvs){ // cmd to quit shell
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

    if(strlen(line) > 0){
        strcpy(history[history_count % MAX_HISTORY], line); // ajout de la cmd a l'historique 
        history_count++;
    }

    tokenize(line,argvs);

    if(!gestion_exit(argvs)) 
        break;
    if (strcmp(argvs[0],"cd") == 0){
        cd_execute(argvs);
        continue;
    }

    if(strcmp(argvs[0],"history") == 0){ // lecture and print de l'historique 
        int start = 0;
        if(history_count > MAX_HISTORY)
            start = history_count - MAX_HISTORY;
        for (int i=start; i < history_count; i++){
            printf("%d %s\n", i+1, history[i % MAX_HISTORY]);
        }
        continue;
    }

    execute(argvs);
    }
}