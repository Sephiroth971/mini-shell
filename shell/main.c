#include <stdio.h>
#include <string.h>

void tokenize(char *line){
    char *token = strtok(line," \t");
    while(token != NULL){
        printf("%s ", token);
        token = strtok(NULL," \t");
    }
}
void read_line(char *line){
        fgets(line,256,stdin);
    size_t len = strlen(line);
    if (line[len - 1]=='\n'){
        line[len - 1]='\0';
    }
}

int main(){
    char line[256];
    printf("shell>>");
    read_line(line);
    tokenize(line);
    
}