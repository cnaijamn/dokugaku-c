#include <stdint.h>
#include <stdio.h>
#include <khash.h>

KHASH_MAP_INIT_INT64(xxx, uint32_t)

int
main(void)
{
	puts("###\n### INIT\n###");
	khash_t(xxx) *h = kh_init(xxx);
	printf("size=%d, buckets=%d\n",
	    kh_size(h),
	    kh_n_buckets(h));
	// size=0, buckets=0

	puts("###\n### PUT\n###");
	int ret;
	for (int i = 100; i <= 300; i += 100) {
		khiter_t k = kh_put(xxx, h, i, &ret);
		kh_value(h, k) = i * 1000;
	}
	printf("size=%d, buckets=%d\n", kh_size(h), kh_n_buckets(h));
	// size=3, buckets=4

	puts("###\n### GET\n###");
	for (int i = 100; i <= 300; i += 100) {
		khiter_t k = kh_get(xxx, h, i);
		printf("key=%d : value=%u\n",
		    i,
		    kh_value(h, k));
		// key=100 : value=100000
		// key=200 : value=200000
		// key=300 : value=300000
	}

	puts("###\n### ITERATOR\n###");
	for (khiter_t k = kh_begin(h); k != kh_end(h); ++k) {
		// if (kh_exist(h, k)) ... をしないと、未使用キーも引っかかるので注意
		printf("key=%lu : value=%u\n",
		    kh_key(h, k),
		    kh_value(h, k));
		// key=100 : value=100000
		// key=200 : value=200000
		// key=0 : value=0
		// key=300 : value=300000
	}

	puts("###\n### EXISTS?\n###");
	khiter_t k1 = kh_get(xxx, h, 100);
	printf("key=100 exists?: value=%d\n",
	    kh_exist(h, k1));
	// key=100 exists?: value=1
	khiter_t k4 = kh_get(xxx, h, 400);
	printf("key=400 exists?: value=%d\n",
	    kh_exist(h, k4));
	// key=400 exists?: value=0

	puts("###\n### DELETE\n###");
	khiter_t k2 = kh_get(xxx, h, 200);
	kh_del(xxx, h, k2);
	for (khiter_t k = kh_begin(h); k != kh_end(h); ++k) {
		if (kh_exist(h, k))
			printf("key=%lu : value=%u\n",
			    kh_key(h, k),
			    kh_value(h, k));
		// key=100 : value=100000
		// key=300 : value=300000
	}
	printf("size=%d, buckets=%d\n", kh_size(h), kh_n_buckets(h));
	// size=2, buckets=4

	puts("###\n### CLEAR\n###");
	kh_clear(xxx, h);
	for (khiter_t k = kh_begin(h); k != kh_end(h); ++k) {
		if (kh_exist(h, k))
			printf("key=%lu : value=%u\n",
			    kh_key(h, k),
			    kh_value(h, k));
	}
	printf("size=%d, buckets=%d\n", kh_size(h), kh_n_buckets(h));
	// size=0, buckets=4

	// TODO kh_resize
	// TODO kh_foreach
	// TODO kh_foreach_value

	kh_destroy(xxx, h);

	return (0);
}
