#include <stdio.h>
#include <string.h>
int main(){
    char line[256];
    printf("shell>>");
    fgets(line,256,stdin);
    size_t len = strlen(line);
    if (line[len - 1]=='\n'){
        line[len - 1]='\0';
    }
    char *token = strtok(line," \t");
    while(token != NULL){
        printf("%s ", token);
        token = strtok(NULL," \t");
    }
    
}