// demonstrating unsafe strcat 

#include <stdio.h>
#include <string.h>

int main(void){
    char out[50]; // risk of buffer overflow
    char user[80] = "Giselle %x %x %s";

    // unsafe usgae of strcat
    strcpy(out, "user = ");
    strcat(out, user);
    strcat(out, " id = 2468");

    // unsafe usage of printf
    printf(out);

    return 0;
}