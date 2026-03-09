#include <stdint.h>
#include <stdio.h>
#include <kvec.h>

typedef kvec_t(double) vec_dbl_t;
//=> typedef struct { size_t n, m; double *a; } vec_dbl_t;

static void
foo(vec_dbl_t *data)
{
	kv_push(double, *data, 990.);
	kv_push(double, *data, 991.);
	kv_push(double, *data, 992.);
}

int
main(void)
{
	puts("###\n### kvec_t(uint32_t)\n###");
	{
		kvec_t(uint32_t) vec;
		kv_init(vec);
		printf("size=%zu, max=%zu\n", kv_size(vec), kv_max(vec));
		// size=0, max=0

		kv_push(uint32_t, vec, 10); // vec[0] = 10
		kv_pushp(uint32_t, vec);    // vec[1] = 0
		kv_push(uint32_t, vec, 20); // vec[2] = 20
		printf("size=%zu, max=%zu\n", kv_size(vec), kv_max(vec));
		// size=3, max=4

		for (size_t i = 0; i < kv_size(vec); i++) {
			printf("vec[%zu] = %u\n", i, kv_A(vec, i));
			// vec[0] = 10
			// vec[1] = 0
			// vec[2] = 20
		}

		printf("pop=%u\n", kv_pop(vec));
		// pop=20
		printf("size=%zu, max=%zu\n", kv_size(vec), kv_max(vec));
		// size=2, max=4

		kv_destroy(vec);
	}

	puts("###\n### vec_dbl_t\n###");
	{
		vec_dbl_t data;
		kv_init(data);
		kv_resize(double, data, 5);
		printf("size=%zu, max=%zu\n", kv_size(data), kv_max(data));
		// size=0, max=5

		foo(&data);
		for (size_t i = 0; i < kv_size(data); i++) {
			printf("data[%zu] = %f\n", i, kv_A(data, i));
			// data[0] = 990.0000000
			// data[1] = 991.0000000
			// data[2] = 992.0000000
		}

		kv_destroy(data);
	}

	return (0);
}
