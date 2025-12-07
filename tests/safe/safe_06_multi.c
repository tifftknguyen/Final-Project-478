
#include <stdio.h>

int main(void) {
    const char *name = "alice";
    int id = 1001;
    unsigned level = 3U;

    printf("name=%s id=%d level=%u\n", name, id, level);
    return 0;
}
