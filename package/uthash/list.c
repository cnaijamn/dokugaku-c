// ref.
// https://github.com/troydhanson/uthash/blob/master/doc/utlist.txt
#include <stdio.h>
#include <string.h>
#include <utlist.h>

struct foo_t {
	int id;
	char name[20];
	struct foo_t *prev, *next;
};

static int
foo_cmp(struct foo_t *a, struct foo_t *b)
{
	return strcmp(a->name, b->name);
}

int
main(void)
{
	struct foo_t *head = NULL;

	struct foo_t f1 = { .id = 1, .name = "Taro" };
	DL_APPEND(head, &f1);
	struct foo_t f2 = { .id = 2, .name = "Jiro" };
	DL_APPEND(head, &f2);
	struct foo_t f3 = { .id = 3, .name = "Saburo" };
	DL_APPEND(head, &f3);
	struct foo_t f4 = { .id = 4, .name = "Hanako" };
	DL_APPEND(head, &f4);

	{
		struct foo_t *elm;
		int count;

		DL_SORT(head, foo_cmp);
		DL_FOREACH(head, elm) {
			printf("%d:%s\n", elm->id, elm->name);
		}
		DL_COUNT(head, elm, count);
		printf("count=%d\n", count);
	}

	{
		struct foo_t *elm, s = { .name = "Jiro" };

		DL_SEARCH(head, elm, &s, foo_cmp);
		if (elm)
			printf("found: %d:%s\n", elm->id, elm->name);
	}

	{
		struct foo_t *elm, *tmp;

		DL_FOREACH_SAFE(head, elm, tmp) {
			DL_DELETE(head, elm);
			// ここで各要素の後始末を行う
		}
		// 全削除されたので表示ゼロ
		DL_FOREACH(head, elm) {
			printf("%d:%s\n", elm->id, elm->name);
		}
	}

	return (0);
}
