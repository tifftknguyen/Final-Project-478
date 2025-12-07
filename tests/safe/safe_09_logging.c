
#include <stdio.h>

int main(void) {
    const char *user = "tiffnguyen";
    const char *action = "login";

    FILE *f = fopen("log.txt", "w");
    if (!f) {
        return 1;
    }

    fprintf(f, "[info] user=%s action=%s\n", user, action);
    fclose(f);
    return 0;
}
