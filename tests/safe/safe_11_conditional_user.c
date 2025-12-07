
#include <stdio.h>
#include <string.h>

int main(void) {
    char msg[64] = "ALL SYSTEMS WORKING ACCORDING TO PLAN";

    if (strlen(msg) < 60) {
        printf("Message: %s\n", msg);
    }
    return 0;
}