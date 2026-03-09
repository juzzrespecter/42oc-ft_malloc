#include "../inc/malloc.h"

//void *mmap(void *addr, size_t length, int prot, int flags,
//                  int fd, off_t offset);

// r sysconf(_SC_PAGESIZE)
// getrlimit(2 

t_memalloc_arena_node *memalloc_arena_head;

void    *ft_malloc(size_t size)
{
    // propositos de testeo

    void *mem_ptr = mmap(0, size, PROT_WRITE|PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

    if (!mem_ptr) {
        return NULL;
    }
    return mem_ptr;
}
