#include <stdio.h>
#include <string.h>

char **tokenize(char *line, char **argvs){
    char *token = strtok(line," \t");
    int i=0;
    while(token != NULL){
        argvs[i] = token;
        i++;
        token = strtok(NULL," \t");
    }
    return argvs;
}
void read_line(char *line){
    fgets(line,256,stdin);
    size_t len = strlen(line);
    if (line[len - 1]=='\n'){
        line[len - 1]='\0';
    }
}
void execute(char *line){

}
int main(){
    char line[256];
    char *argvs[20];
    printf("shell>>");
    read_line(line);
    tokenize(line,argvs);
    for (int i = 0; argvs[i] != NULL; i++) {
    printf("argvs[%d] = %s\n", i, argvs[i]);
}

    
}