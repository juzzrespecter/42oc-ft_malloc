#include "malloc.h"
#include <stdio.h>
#include <mcheck.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>

void memcheck_non_free() {
	void *_ptr;
	srand(time(NULL));
	char c = rand() % 25 + 64;

	_ptr = malloc(640000);
	((char *)_ptr)[25000] = c;
	((char *)_ptr)[25001] = 'b';
	((char *)_ptr)[25002] = 0;
	write(1, _ptr + 25000, 3);
	return ;
}

void assert_malloc_trace() {
	char *mtrace_path = getenv("MALLOC_TRACE");
	assert(mtrace_path != NULL);
	printf("[MALLOC_TRACE] debug mem trace into %s\n", mtrace_path);
}

int main() {
	mtrace();
	assert_malloc_trace();
	printf("Comienza ultratest: \n");

	char * test = malloc(123);
	test[0] = 'a';
	test[1] = 0;
	printf("Finaliza ultratest... (%s)\n", test);

	//free(test);
	memcheck_non_free();
	test = (char *)&test;
	muntrace();
	exit(0);
}
