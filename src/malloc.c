#include "../inc/malloc.h"

//void *mmap(void *addr, size_t length, int prot, int flags,
//                  int fd, off_t offset);

// r sysconf(_SC_PAGESIZE)
// getrlimit(2 

#define DEBUG_MSG "[DEBUG] malloc() call\n"

#include <stdio.h>


//t_memalloc_arena_node *memalloc_arena_head;
//static t_memalloc_arena_node *test_node;

void *malloc(size_t size)
{
    // propositos de testeo

    size_t pad_size = size + 8;
    void *mem_ptr = mmap(0, pad_size, PROT_WRITE|PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

    write(1, DEBUG_MSG, sizeof(DEBUG_MSG));
    if (MAP_FAILED == mem_ptr) {
        perror("malloc: mmap");
        return NULL;
    }
    ((size_t *)mem_ptr)[0] = size;
    return mem_ptr + 8;
}
