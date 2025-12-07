// demonstrating unsafe direct parameter access

#include <stdio.h>

int main(int argc, char *argv[]){
    int secret = 1234;

    // vulnerable
    if (argc > 1){
        printf(argv[1], &secret);
    } else {
        printf("Usage: %s <format-string \n", argv[0]);
    
    }
    return 0;
}
