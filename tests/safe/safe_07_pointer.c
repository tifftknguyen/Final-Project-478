
#include <stdio.h>

int main(void) {
    int x = 10;
    printf("x_ptr=%p val=%d\n", (void *)&x, x);
    return 0;
}
