#include <pthread.h>
#ifndef __DEFAULT_SOURCE
#  define __DEFAULT_SOURCE
#endif
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


static const size_t tdata_init = 32;

void *do_malloc(size_t size) {
    void *ptr = malloc(size);
    pthread_t pid = pthread_self();
    printf("Called malloc from PID (%ld) with size (%ld): (%p)\n", pid, size, ptr);
    getchar();
    return ptr;
}

void *routine(void *unused) {
    while(1) {
    size_t size = rand();
    getchar();
    do_malloc(size);
    }
}

int main() {
    extern __thread int errno;
    pthread_t t1, t2, t3;
    printf("errno: %d\n", errno);

    printf("Init... (%d)\n", getpid());
    getchar();
    fflush(stdin);

    pthread_create(&t1, NULL, routine, NULL);
    pthread_create(&t2, NULL, routine, NULL);
    pthread_create(&t3, NULL, routine, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    exit(0);
}