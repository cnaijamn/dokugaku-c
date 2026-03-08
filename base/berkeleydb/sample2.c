#include <db.h>
#include <err.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

// 構造体データ

typedef struct {
	size_t id;
	char name[32];
} foo_t;

int
main(void)
{
	puts("###\n### Create Database\n###");
	{
		DB *db = dbopen(
		    "./test2.db",
		    O_CREAT|O_TRUNC|O_RDWR, 0644,
		    DB_BTREE,
		    NULL
		);
		if (!db) err(1, "dbopen");

		char kbuf[64];
		for (int i = 1; i <= 5; i++) {
			foo_t foo = { .id = i, .name = {0} };
			sprintf(kbuf, "%d", i);
			sprintf(foo.name, "NAME_%03d", i);
			int ret = db->put(
			    db,
			    &(DBT){ .data = kbuf, .size = strlen(kbuf) },
			    &(DBT){ .data = &foo, .size = sizeof(foo_t) },
			    R_NOOVERWRITE
			);
			// ret -> 0:success, 1:override, -1:error
			if (ret == 0)
				printf("[put] id => %zu, name => %s\n",
				    foo.id, foo.name);
			else
				warnx("db->put return %d", ret);
		}

		db->close(db);
	}

	puts("###\n### Random Access\n###");
	{
		DB *db = dbopen(
		    "./test2.db",
		    O_RDONLY, 0644,
		    DB_BTREE,
		    NULL
		);
		if (!db) err(1, "dbopen");

		DBT data = {0};
		int ret = db->get(
		    db,
		    &(DBT){ .data = "3", .size = 1 },
		    &data,
		    0
		);
		// ret -> 0:success, 1:notexist, -1:error
		if (ret == 0) {
			foo_t *foo = (foo_t *)data.data;
			printf(
			    "[get] id => %zu, name => %s\n",
			    foo->id, foo->name
			);
		} else
			warnx("db->get return %d", ret);

		db->close(db);
	}

	return (0);
}
