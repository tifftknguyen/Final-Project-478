// Demonstrating unsafe environment variable 

#include <stdio.h>
#include <stdlib.h>

int main(void){
    char *term = getenv("TERM");

    if (term){
        printf(term);
    }
    
    return 0;
}