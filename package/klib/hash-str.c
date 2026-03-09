#include <stdio.h>
#include "_show_alloc.h"
#include <khash.h>

// HashMapのkeyをchar*
// HashMapのvalueにstructを格納
typedef struct {
	int id;
	char name[16];
} xxx; // sizeof(xxx) = 20byte

KHASH_MAP_INIT_STR(xxx, xxx)

int
main(void)
{
	puts("<<kh_init>>");
	khash_t(xxx) *h = kh_init(xxx);
	printf("size=%d, buckets=%d\n",
	    kh_size(h),
	    kh_n_buckets(h));
	// size=0, buckets=0

	puts("###\n### PUT\n###");
	int ret;
	char buf[32];
	for (int i = 100; i <= 300; i += 100) {
		sprintf(buf, "KEY-%d", i);
		puts("<<kh_put>>");
		khiter_t k = kh_put(xxx, h, buf, &ret);

		puts("<<kh_key>>");
		//kh_key(h, k) = buf; // これじゃ駄目
		kh_key(h, k) = strdup(buf);

		puts("<<kh_value>>");
		kh_value(h, k).id = i * 1000;
		sprintf(kh_value(h, k).name,
		    "xxx-name-%d", i * 1000);
	}
	printf("size=%d, buckets=%d\n", kh_size(h), kh_n_buckets(h));
	// size=3, buckets=4

	puts("###\n### GET\n###");
	for (int i = 100; i <= 300; i += 50) {
		sprintf(buf, "KEY-%d", i);
		khiter_t k = kh_get(xxx, h, buf);
		printf("%s : %u - %s\n",
		    kh_key(h, k),
		    kh_value(h, k).id,
		    kh_value(h, k).name);
		// KEY-100 : 100000 - xxx-name-100000
		// (null) : 0 - 
		// KEY-200 : 200000 - xxx-name-200000
		// ...
	}

	puts("###\n### FREE KEYS\n###");
	for (khiter_t k = kh_begin(h); k != kh_end(h); ++k) {
		if (kh_exist(h, k)) {
			printf("%s : clear\n", 
			    kh_key(h, k));
			free((void*)kh_key(h, k));
			// KEY-100 : clear
			// KEY-200 : clear
			// ...
		}
	}

	puts("<kh_destroy>");
	kh_destroy(xxx, h);

	return (0);
}
