#include <stdio.h>
#include <stdlib.h>

inline static void *
_kcalloc(size_t n, size_t sz)
{
	void *ret = calloc(n, sz);
	printf("[kcalloc n=%zu, sz=%zu] => %p\n", n, sz, ret);
	return ret;
}

inline static void *
_kmalloc(size_t sz)
{
	void *ret = malloc(sz);
	printf("[kmalloc sz=%zu] => %p\n", sz, ret);
	return ret;
}

inline static void *
_krealloc(void *p, size_t sz)
{
	void *ret = realloc(p, sz);
	printf("[krealloc p=%p, sz=%zu] => %p\n", p, sz, ret);
	return ret;
}

inline static void
_kfree(void *p)
{
	printf("[kfree p=%p]\n", p);
	return free(p);
}

#define kcalloc(__n, __sz)	_kcalloc(__n, __sz)
#define kmalloc(__sz)		_kmalloc(__sz)
#define krealloc(__p, __sz)	_krealloc(__p, __sz)
#define kfree(__p)		_kfree(__p)
