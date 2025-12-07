
#include <stdio.h>

int main(void) {
    char line[128] = "tiffnguyen";
    char username[16];

    if (sscanf(line, "%15s", username) == 1) {
        printf("user=%s\n", username);
    }
    return 0;
}
