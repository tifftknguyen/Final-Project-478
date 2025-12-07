// Demonstrating user input vulnerability 

#include <stdio.h>

int main(void){
    char user_format_buffer[64];

    printf("Enter sentence: ");
    
    if (fgets(user_format_buffer, sizeof(user_format_buffer), stdin) == NULL) {
        return 1;
    }

    // OUR VULNERABLE LINE
    printf(user_format_buffer);
    return 0;
}