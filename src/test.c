#include "malloc.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <sys/resource.h>

static void capture_mapped_segment_bounds(char* segment, void* ptr) {
    regex_t re;
    int re_comp = regcomp(&re, "^([a-z0-9]+)-([a-z0-9]+) ", REG_EXTENDED);
    char buffer[100];

    if (re_comp) {
        fprintf(stderr, "Could not compile\n");
        return ;
    }
    re_comp = regexec(&re, segment, 0, NULL, 0);
    if (!re_comp) {
        printf("Match\n");
    }
    if (re_comp == REG_NOMATCH) {
        printf("No match\n");
    }
}

static void get_mapped_segment(void *ptr_to_track) {
    pid_t pid = getpid();
    char cmd_buffer[50];
    char output[200];
    FILE *popen_stream;



//    sprintf(cmd_buffer, "cat /proc/%d/maps | grep %p", pid, ptr_to_track);
    sprintf(cmd_buffer, "cat /proc/%d/maps", pid);
    printf(cmd_buffer);
    popen_stream = popen(cmd_buffer, "r");
    if (!popen_stream) {
        perror("popen");
        return ;
    }
    while (fgets(output, sizeof output, popen_stream)) {
        capture_mapped_segment_bounds(output, ptr_to_track);
        printf("%s", output);
    }
    fclose(popen_stream);
}   

void* do_malloc(size_t size) {
    void *ptr = malloc(size);
    printf("Called malloc with size (%ld): (%p)\n", size, ptr);
    get_mapped_segment(ptr);
    getchar();
    return ptr;
}

int main(int argc, char **argv) {
    pid_t pid = getpid();
    printf("Starting process with pid (%d)\n", pid);

    struct rlimit rlim;
    memset(&rlim, 0, sizeof(struct rlimit));
    int ret = getrlimit(RLIMIT_AS, &rlim);
    if (ret < 0) {
        perror("getrlimit");
        exit(1);
    }
    printf("rlimit call: curr (%ld), max (%ld)\n", rlim.rlim_cur, rlim.rlim_max);
    getchar();


    do_malloc(10);
    do_malloc(20);
    do_malloc(30);

    do_malloc(100000);
    do_malloc(200000);
    do_malloc(2000000000);
    do_malloc(2000000000);

    exit(0);
}
