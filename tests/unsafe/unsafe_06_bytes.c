// Demonstrating unsafe # of characters printed

#include <stdio.h>
int main(void){
int write_memory = 0;

printf("Bytes written to memory: %n \n", &write_memory);
printf("written = %d \n", write_memory);
return 0;
}