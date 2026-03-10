#include "../inc/malloc.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <sys/resource.h>

# define RED "\033[31m"
# define END "\033[0m"

static int capture_mapped_segment_bounds(char* segment, void* ptr) {
    regex_t re;
    regmatch_t pmatch[3];
    int re_comp = regcomp(&re, "^([a-z0-9]+)-([a-z0-9]+) ", REG_EXTENDED);
    char buffer[100];

    if (re_comp) {
        fprintf(stderr, "regcomp: Could not compile\n");
        return 0;
    }
    if (REG_NOMATCH == re_comp) {
        return 0;
    }
    re_comp = regexec(&re, segment, 3, pmatch, 0);
    regfree(&re);
    if (!re_comp) {
        unsigned long bound_lo = strtol(segment + pmatch[1].rm_so, NULL, 16);
        unsigned long bound_hi = strtol(segment + pmatch[2].rm_so, NULL, 16);

        if ((unsigned long)ptr >= bound_lo && (unsigned long)ptr <= bound_hi) {
            return 1;
        } else {
            return 0;
        }
    }
}

static void get_mapped_segment(void *ptr_to_track) {
    pid_t pid = getpid();
    char cmd_buffer[50];
    char output[200];
    FILE *popen_stream;

//    sprintf(cmd_buffer, "cat /proc/%d/maps | grep %p", pid, ptr_to_track);
    sprintf(cmd_buffer, "cat /proc/%d/maps\n", pid);
    printf(cmd_buffer);
    popen_stream = popen(cmd_buffer, "r");
    if (!popen_stream) {
        perror("popen");
        return ;
    }
    while (fgets(output, sizeof output, popen_stream)) {
        if (capture_mapped_segment_bounds(output, ptr_to_track)) {
            printf(RED "%s" END, output);
        } else {
            printf("%s", output);
        }
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
    getchar();

    do_malloc(100000);
    do_malloc(200000);
    do_malloc(2000000000);
    do_malloc(2000000000);
    getchar();

    exit(0);
}
