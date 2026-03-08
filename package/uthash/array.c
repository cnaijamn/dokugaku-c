// ref.
// https://github.com/troydhanson/uthash/blob/master/doc/utarray.txt
#include <stdio.h>
#include <string.h> // strdup
#include <assert.h>
#include <utarray.h>

// struct (complex)
struct bar_t {
	int a;
	char *s;
};

static void
bar_init(void *_elt)
{
	struct bar_t *elt = (struct bar_t *)_elt;
	elt->a = 999;
	elt->s = strdup("!!!");
	printf("bar_init: (elt.a, elt.s) = (%d, \"%s\")\n",
	    elt->a, elt->s);
}

static void
bar_copy(void *_dst, const void *_src)
{
	struct bar_t *dst = (struct bar_t *)_dst;
	struct bar_t *src = (struct bar_t *)_src;
	dst->a = src->a;
	dst->s = src->s ? strdup(src->s) : NULL;
	printf("bar_copy: (src.a, src.s, dst.a, dst.s)"
	    " = (%d, \"%s\", %d, \"%s\")\n",
	    src->a, src->s, dst->a, dst->s);
}

static void
bar_dtor(void *_elt)
{
	struct bar_t *elt = (struct bar_t *)_elt;
	printf("bar_dtor: (elt.a, elt.s) = (%d, \"%s\")\n",
	    elt->a, elt->s);
	if (elt->s)
		free(elt->s);
}

int
main(void)
{
	puts("###\n### int\n###");
	{
		UT_array *nums;

		utarray_new(nums, &ut_int_icd);

		// push
		for (int i = 5; i < 8; i++)
			utarray_push_back(nums, &i);
		printf("len: %d\n", utarray_len(nums));

		// iterate
		for (int *p = (int *)utarray_front(nums);
		    p != NULL;
		    p = (int *)utarray_next(nums, p))
			printf("%p : %d\n", p, *p);

		utarray_free(nums);
	}

	puts("###\n### string\n###");
	{
		UT_array *strs;

		utarray_new(strs, &ut_str_icd);

		// push
		char *s;
		s = "hello"; utarray_push_back(strs, &s);
		s = "world"; utarray_push_back(strs, &s);
		printf("len: %d\n", utarray_len(strs));

		// iterate
		char **p = NULL;
		while ((p = (char **)utarray_next(strs, p)))
			printf("%p : %s\n", p, *p);

		utarray_free(strs);
	}

	puts("###\n### struct (simple)\n###");
	{
		struct foo_t {
			int a;
			float b;
		};

		UT_array *foos;
		UT_icd foo_t_icd = { sizeof(struct foo_t), NULL, NULL, NULL };

		utarray_new(foos, &foo_t_icd);

		// push
		//struct foo_t foo;
		//foo.a = 1; foo.b = 1.1; utarray_push_back(foos, &foo);
		//foo.a = 2; foo.b = 2.2; utarray_push_back(foos, &foo);
		utarray_push_back(foos, (&(struct foo_t){ 1, 1.1 }));
		utarray_push_back(foos, (&(struct foo_t){ 2, 2.2 }));
		printf("len: %d\n", utarray_len(foos));

		// iterate
		struct foo_t *p;
		for (p = (struct foo_t *)utarray_front(foos);
		    p != NULL;
		    p = (struct foo_t *)utarray_next(foos, p))
			printf("%p : %d %f\n", p, p->a, p->b);

		utarray_free(foos);
	}

	puts("###\n### struct (complex)\n###");
	{
		UT_array *bars;
		UT_icd bar_t_icd = {
		    sizeof(struct bar_t), bar_init, bar_copy, bar_dtor };

		utarray_new(bars, &bar_t_icd);

		// push
		//struct bar_t bar;
		//bar.a = 1; bar.s = "hello"; utarray_push_back(bars, &bar);
		//bar.a = 2; bar.s = "world"; utarray_push_back(bars, &bar);
		// called bar_copy()
		utarray_push_back(bars, (&(struct bar_t){ .a = 1, .s = "hello"}));
		utarray_push_back(bars, (&(struct bar_t){ .a = 2, .s = "world"}));

		// extend back
		utarray_extend_back(bars); // called bar_init()
		printf("len: %d\n", utarray_len(bars)); // 3

		// resize
		utarray_resize(bars, 5); // called bar_init()
		printf("len: %d\n", utarray_len(bars)); // 5
		utarray_resize(bars, 4); // called bar_dtor()
		printf("len: %d\n", utarray_len(bars)); // 4

		// eltptr
		struct bar_t *elt;
		elt = utarray_eltptr(bars, 1);
		printf("eltptr(1): (elt.a, elt.s) = (%d, \"%s\")\n", elt->a, elt->s); // (2, "world")
		elt = utarray_eltptr(bars, 4);
		assert(elt == NULL);

		// iterate
		struct bar_t *p;
		for (p = (struct bar_t *)utarray_front(bars);
		    p != NULL;
		    p = (struct bar_t *)utarray_next(bars, p))
			printf("%p : %d \"%s\"\n", p, p->a, p->s);

		utarray_free(bars);
	}

	return (0);
}
