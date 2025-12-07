// demonstrating bad practic snprintf overflow 

#include <stdio.h>

int main(void){
    char buf[16];
    char input[128];

    printf("Enter message: ");

    if (fgets(input, sizeof(input), stdin) == NULL){
        return 1;
    }
    // buffer overflow
    snprintf(buf, 128, "%s", input);

    printf(buf);
    return 0;
}