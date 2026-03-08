#include <stdio.h>
#include <uthash.h>

struct foo_t {
	int id;
	char name[20];
	UT_hash_handle hh;
};

static int
foo_cmpfcn_desc(struct foo_t *a, struct foo_t *b)
{
	// DESC
	return (b->id - a->id);
}

int
main(void)
{
	struct foo_t *foos = NULL;

	puts("### INT ###");
	{
		// key is "id"(int)
		struct foo_t f1 = { .id = 1, .name = "Taro" };
		HASH_ADD_INT(foos, id, &f1);
		struct foo_t f3 = { .id = 3, .name = "Saburo" };
		HASH_ADD_INT(foos, id, &f3);
		struct foo_t f2 = { .id = 2, .name = "Jiro" };
		HASH_ADD_INT(foos, id, &f2);
		struct foo_t f4 = { .id = 4, .name = "Hanako" };
		HASH_ADD_INT(foos, id, &f4);

		puts("--- count");
		size_t c = HASH_COUNT(foos);
		printf(" %zu\n", c); // 3

		struct foo_t *foo, *tmp;

		puts("--- iterate");
		HASH_ITER(hh, foos, foo, tmp) {
			printf(" %d:%s\n", foo->id, foo->name);
			// 1:Taro
			// 3:Saburo
			// 2:Jiro
			// 4:Hanako
		}

		puts("--- sort");
		HASH_SORT(foos, foo_cmpfcn_desc);
		HASH_ITER(hh, foos, foo, tmp) {
			printf(" %d:%s\n", foo->id, foo->name);
			// 4:Hanako
			// 3:Saburo
			// 2:Jiro
			// 1:Taro
		}

		puts("--- find");
		int foo_id = 2;
		HASH_FIND_INT(foos, &foo_id, foo);
		printf(" %d:%s\n", foo->id, foo->name); // 2:Jiro

		puts("--- delete");
		HASH_DEL(foos, foo);
		HASH_FIND_INT(foos, &foo_id, foo);
		printf(" %p\n", foo); // 0x0

		puts("--- all clear");
		HASH_CLEAR(hh, foos);
		c = HASH_COUNT(foos);
		printf(" %zu\n", c); // 0
	}

	puts("### STR ###");
	{
		// key is "name"(char *)
		struct foo_t f1 = { .id = 1, .name = "Taro" };
		HASH_ADD_STR(foos, name, &f1);
		struct foo_t f2 = { .id = 2, .name = "Jiro" };
		HASH_ADD_STR(foos, name, &f2);

		puts("--- iterate");
		struct foo_t *foo, *tmp;
		HASH_ITER(hh, foos, foo, tmp) {
			printf(" %d:%s\n", foo->id, foo->name);
			// 1:Taro
			// 2:Jiro
		}

		puts("--- find");
		char name[16];
		strcpy(name, "Jiro");
		HASH_FIND_STR(foos, name, foo);
		printf(" %d:%s\n", foo->id, foo->name); // 2:Jiro

		// snip...

		HASH_CLEAR(hh, foos);
	}

	return (0);
}
