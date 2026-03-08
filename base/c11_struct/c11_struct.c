#include <stdio.h>

struct foo_t {
	int id;
};

static void
print_foo(struct foo_t *fp)
{
	printf("%d\n", fp->id);
}

int
main(void)
{
	struct foo_t f, *fp;

	f = (struct foo_t){
		.id = 100,
	};
	print_foo(&f);

	fp = &(struct foo_t){
		.id = 200,
	};
	print_foo(fp);

	print_foo(&(struct foo_t){
		.id = 300,
	});

	return (0);
}
