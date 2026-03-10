#include <stdlib.h>

int main() {
    char * allowed_memory = malloc(2000000);
    free(allowed_memory);

    for (int i = 0; i < 50; i++) {
        malloc(2000000);
    }
//    allowed_memory[1] = 'e';
}