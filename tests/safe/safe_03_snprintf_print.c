
#include <stdio.h>

int main(void) {
    char buf[64];
    const char *name = "Tiffany";

    snprintf(buf, sizeof(buf), "Hello %s!", name);
    printf("%s\n", buf);
    return 0;
}
