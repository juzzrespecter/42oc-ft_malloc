#include "malloc.h"
# define DMESG "Entering malloc...\n"
# define DMESG_EXIT "Exiting program successfully...\n"

int main() {
    write(1, DMESG, sizeof DMESG);
    char * test = malloc(420);
    free(test);
    write(1, DMESG_EXIT, sizeof DMESG_EXIT);
}