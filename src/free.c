#include "malloc.h"
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


# define DEBUG_FREE "[DEBUG] free() call\n"
# define DMESG_ERR(x) \
    write(1, "free: munmap: ", sizeof "free: munmap: ");\
    write(1, x, strlen(x));\
    write(1, "\n", 1)

void free(void * ptr) {
    write(1, DEBUG_FREE, sizeof DEBUG_FREE);
    if (!ptr)
        return ;
    void *memchunk_ptr = ptr - 8;
    size_t mem_chunk_size = ((size_t *)memchunk_ptr)[0];
    int _munmap_ret = munmap(memchunk_ptr, mem_chunk_size);
    if (_munmap_ret == -1) {
        DMESG_ERR(strerror(errno));
    }


    return ;
}