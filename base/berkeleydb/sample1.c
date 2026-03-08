#include <db.h>
#include <fcntl.h>
#include <err.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

// 単純なデータ(文字列)

int
main(void)
{
	puts("###\n### Create Database\n###");
	{
		DB *db = dbopen(
		    "./test1.db",
		    O_CREAT|O_TRUNC|O_RDWR, 0644,
		    DB_BTREE,
		    NULL
		);
		if (!db) err(1, "dbopen");

		char kbuf[64], dbuf[64];
		for (int i = 1; i <= 5; i++) {
			sprintf(kbuf, "KEY_%03d", i);
			sprintf(dbuf, "%d", i);
			int ret = db->put(
			    db,
			    &(DBT){ .data = kbuf, .size = strlen(kbuf) },
			    &(DBT){ .data = dbuf, .size = strlen(dbuf) },
			    R_NOOVERWRITE
			);
			// ret -> 0:success, 1:override, -1:error
			if (ret == 0)
				printf("[put] %s : %s\n", kbuf, dbuf);
			else
				warnx("db->put return %d", ret);
		}

		db->close(db);
	}

	puts("###\n### Sequential Access\n###");
	{
		DB *db = dbopen(
		    "./test1.db",
		    O_RDONLY, 0644,
		    DB_BTREE,
		    NULL
		);
		if (!db) err(1, "dbopen");

		DBT key = {0}, data = {0};
		int ret;
		do {
			ret = db->seq(
			    db, 
			    &key,
			    &data,
			    R_NEXT
			);
			// ret -> 0:success, 1:end, -1:error
			if (ret == 0)
				printf(
				    "[seq] %.*s : %.*s\n",
				    (int)key.size, (char *)key.data,
				    (int)data.size, (char *)data.data
				);
			else if (ret == 1)
				puts("[seq] end");
			else
				warnx("db->seq return %d", ret);
		} while (ret == 0);

		db->close(db);
	}

	puts("###\n### Random Access\n###");
	{
		DB *db = dbopen(
		    "./test1.db",
		    O_RDONLY, 0644,
		    DB_BTREE,
		    NULL
		);
		if (!db) err(1, "dbopen");

		DBT data = {0};
		int ret = db->get(
		    db,
		    &(DBT){ .data = "KEY_004", .size = 7 },
		    &data,
		    0
		);
		// ret -> 0:success, 1:notexist, -1:error
		if (ret == 0)
			printf(
			    "[get] KEY_004 => %.*s\n",
			    (int)data.size, (char *)data.data
			);
		else
			warnx("db->get return %d", ret);

		db->close(db);
	}

	//TODO del

	return (0);
}
