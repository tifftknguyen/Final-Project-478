// demonstrating unsafe strcat with bufferflow 

#include <stdio.h>
#include <string.h>

int main(void){
    char dest[32] = "Hello World, ";
    char source [64];

    printf("Name: ");
    if(fgets(source, sizeof(source), stdin) == NULL){
        return 1;
    }

    strcat(dest, source);
    printf("%s \n", dest);
    return 0;
}