#ifndef MALLOC_H
# define MALLOC_H
# ifndef __DEFAULT_SOURCE
#   define _DEFAULT_SOURCE
# endif
# include <sys/mman.h>
# include <unistd.h>
# include <stddef.h>

// DELETE ME LATER
# include <assert.h>

# define M_ARENA_SIZE 4000
# define M_TINY_SIZE
# define M_


typedef struct s_memalloc_chunk_node {

} t_memalloc_chunk_node;

typedef struct s_memalloc_arena_node {
    void *mem_ptr;
    t_memalloc_chunk_node *m_chunck_head;
} t_memalloc_arena_node;

void    free(void *ptr);
void    *malloc(size_t size);
void    *realloc(void *ptr, size_t size);

void    show_alloc_mem();

# endif // MALLOC_H

// primera arena: heap del proceso (after .bss)
// siguientes arenas: mmapada (empezamos desde aqui)