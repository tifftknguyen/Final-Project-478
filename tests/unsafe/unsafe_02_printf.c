// Demonstrating unsafe printf

#include <stdio.h>

int main(void){
    char buf[64];
    char name[32];

    printf("Enter name: ");

    if (fgets(name, sizeof(name), stdin) == NULL){
        return 1;
    }

    snprintf(buf, sizeof(buf), "Hello %s from Tiffany & Giselle! ", name);

    // Vulnerable printf
    printf(buf);
    return 0;
}