#include <assert.h>
#include <gc.h>
#include <stdint.h>
#include <stdio.h>

static void
finalizer(GC_PTR obj, GC_PTR client_data)
{
	int i = (int)(uintptr_t)client_data;
	printf("finalizer: i = %d\n", i);
}

int
main(void)
{
	GC_INIT();

	for (int i = 0; i < 10000000; ++i) {
		int **p = (int **)GC_MALLOC(sizeof(int *));
#if 0
		GC_REGISTER_FINALIZER(p, finalizer, (GC_PTR)(uintptr_t)i, NULL, NULL);
#endif
		int *q = (int *)GC_MALLOC_ATOMIC(sizeof(int));
		assert(*p == 0);
		*p = (int *)GC_REALLOC(q, 2 * sizeof(int));

		if (i % 100000 == 0)
			printf("Heap size = %zu\n", GC_get_heap_size());
	}

	return (0);
}
