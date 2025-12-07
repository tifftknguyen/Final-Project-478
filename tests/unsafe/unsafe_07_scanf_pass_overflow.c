// Demonstrating passwording with unsafe scanf

#include <stdio.h>

int main(void){
    char password[16];

    printf("Enter password: ");

    if (scanf("%s", password) != 1){
        return 1;
    }
    printf("You entered: %s \n", password);
    return 0;
}