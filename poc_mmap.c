# ifndef __DEFAULT_SOURCE
#   define _DEFAULT_SOURCE
# endif
#include <sys/mman.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void *do_mmap(size_t size) {
    void *ptr = mmap(NULL, size, PROT_READ, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
    if (!ptr) {
        perror("mmap");
        exit(1);
    }
    printf("Calling mmap with size (%ld): (%p)\n", size, ptr);
    getchar();
    return ptr;
}

int main() {
    printf("Init poc_mmap with pid: (%d)\n", getpid());
    getchar();

    do_mmap(1);
    do_mmap(10);
    do_mmap(100000);
    do_mmap(200000);
    do_mmap(10000000);
    do_mmap(10000000);
    do_mmap(10000000000);
    do_mmap(10000000000);
    exit(0);
}