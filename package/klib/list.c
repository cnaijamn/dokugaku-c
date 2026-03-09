#include <stdint.h>
#include <stdio.h>
#include <klist.h>

KLIST_INIT(xxx, uint32_t, free);

int
main(void)
{
	klist_t(xxx) *lst = kl_init(xxx);

	puts("###\n### push\n###");
	for (int i = 1; i <= 3; i++) {
		*kl_pushp(xxx, lst) = i * 100;
	}

	puts("###\n### iter\n###");
	for (kliter_t(xxx) *p = kl_begin(lst);
	    p != kl_end(lst);
	    p = kl_next(p)) {
		printf("item: %u\n", kl_val(p));
		// item: 100
		// item: 200
		// item: 300
	}

	puts("###\n### shift\n###");
	uint32_t v;
	kl_shift(xxx, lst, &v);
	printf("shifted: %u\n", v); // 100

	for (kliter_t(xxx) *p = kl_begin(lst);
	    p != kl_end(lst);
	    p = kl_next(p)) {
		printf("item: %u\n", kl_val(p));
		// item: 200
		// item: 300
	}

	kl_destroy(xxx, lst);

	return (0);
}
