// Demonstrating string with missing arguments

#include <stdio.h>

int main(void){
    const char *status = "operational %x %x %s\n";

// Vulnerable line
    printf(status);
    return 0;
}