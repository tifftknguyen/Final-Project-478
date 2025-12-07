
#include <stdio.h>

int main(void) {
    char out[64];
    const char *user = "alice";
    int id = 7;

    snprintf(out, sizeof(out), "user=%s id=%d", user, id);
    printf("%s\n", out);
    return 0;
}
