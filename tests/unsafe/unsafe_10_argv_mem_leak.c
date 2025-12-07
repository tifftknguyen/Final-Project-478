// demonstrating argv causing memory overflow 

#include <stdio.h>

int main(int argc, char *argv[]){
    if (argc > 1){
        printf(argv[1]);
        printf("\n");
    
    } else {

     printf("Usage: %s <format-string> \n", argv[0]);
}
    return 0;
}