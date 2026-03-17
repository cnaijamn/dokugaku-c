#include <gc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void
finalizer(GC_PTR obj, GC_PTR client_data)
{
	printf("finalizer called: %s\n", (char *)client_data);
	fflush(stdout);
}

typedef struct _cell_t {
	void *head;
	struct _cell_t *tail;
} cell_t;

static cell_t *
cons(void *head, cell_t *tail)
{
	cell_t *cell = (cell_t *)GC_MALLOC(sizeof(cell_t));
	GC_REGISTER_FINALIZER(cell, finalizer, (GC_PTR)"...x1", NULL, NULL);
	if (cell) {
		cell->head = head;
		cell->tail = tail;
	}
	return (cell);
}

int
main(void)
{
	cell_t *lst = NULL;

	GC_INIT();

	lst = cons("x1", lst);
	GC_REGISTER_FINALIZER(lst, finalizer, (GC_PTR)"x1", NULL, NULL);
	lst = cons("x2", lst);
	GC_REGISTER_FINALIZER(lst, finalizer, (GC_PTR)"x2", NULL, NULL);
	lst = cons("x3", lst);
	GC_REGISTER_FINALIZER(lst, finalizer, (GC_PTR)"x3", NULL, NULL);

	// 参照を切る
	lst = NULL;

	// ここでは結果をすぐに見たいため、GCを複数回実行することで無理やりlstの全要素を解放している
	// 実際にはこんなことしなくても大丈夫
	GC_gcollect(); // "finalizer called: x3"
	GC_gcollect(); // "finalizer called: x2"
	GC_gcollect(); // "finalizer called: x1"

	return (0);
}
