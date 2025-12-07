// Demonstrating unsafe log in 

#include <stdio.h>

int main(void) {
    const char *user = "Giselle";
    const char *action = "login-ok";

    const char *fmt = "leak: %x %x %s\n";

    FILE *f = fopen("log.txt", "a");

    if (f) {
        fprintf(f, fmt);
        fclose(f);
    }

    printf("Logged In\n");
    return 0;
}