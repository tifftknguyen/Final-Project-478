// demonstrating unsafe strcpy resulting in overflow

#include <stdio.h>
#include <string.h>

int main(void){
    char source[256];
    char dest[32];

    printf("Enter text: ");

    if (fgets(source, sizeof(source), stdin) == NULL){
        return 1;
    }

    strcpy(dest, source);
    printf("Stored: %s \n", dest);
    return 0;
}