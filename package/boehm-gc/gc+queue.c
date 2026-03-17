// TAILQとGCの組み合わせテスト
#include <assert.h>
#include <gc.h>
#include <stdio.h>
#include <sys/queue.h>
#include <unistd.h>

typedef struct _datum_t {
	TAILQ_ENTRY(_datum_t) tailq;
	int id;
	float val;
} datum_t;

typedef struct {
	TAILQ_HEAD(datahead, _datum_t) data;
} foo_t;

static void
foo_init(foo_t *f)
{
	TAILQ_INIT(&f->data);
	//printf("%p\n", TAILQ_FIRST(&f->data));
}

static void
datum_finalizer(GC_PTR obj, GC_PTR client_data)
{
	datum_t *d = (datum_t *)obj;
	printf("datum_finalizer: id=%d, value=%f\n", d->id, d->val);
	fflush(stdout);
}

static void
foo_add(foo_t *f, int id, float val)
{
	datum_t *d;

	//d = (datum_t *)GC_MALLOC_ATOMIC(sizeof(datum_t));
	//NOTE: GC_MALLOC_ATOMICだと、問答無用でGC_galloc()の対象になるので注意
	d = (datum_t *)GC_MALLOC(sizeof(datum_t));
	assert(d);

	GC_REGISTER_FINALIZER(d, datum_finalizer, (GC_PTR)0, NULL, NULL);

	d->id = id;
	d->val = val;

	TAILQ_INSERT_TAIL(&f->data, d, tailq);
}

static void
foo_delete(foo_t *f, int id)
{
	datum_t *d;

	TAILQ_FOREACH(d, &f->data, tailq) {
		if (d->id == id) {
			TAILQ_REMOVE(&f->data, d, tailq);
			printf("foo_delete: id=%d\n", id);
			fflush(stdout);
			return;
		}
	}
}

int
main(void)
{
	foo_t f0;

	GC_INIT();

	foo_init(&f0);

	for (int id = 1; id <= 1000; id++) {
		foo_add(&f0, id, id * 1.1);
	}

	foo_delete(&f0, 5);
	foo_delete(&f0, 7);

	GC_gcollect(); // id=5,7のみGC対象になる
	sleep(3);

	return (0);
}
