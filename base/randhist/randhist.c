#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX	(15)
#define ITE	(500)

//#define RANDTYPE	1 /* rand */
//#define RANDTYPE	2 /* random */
//#define RANDTYPE	3 /* arc4random */
#define RANDTYPE	4 /* arc4random_uniform */

#if RANDTYPE >= 1 && RANDTYPE <= 2 /* for rand() or random() */
__attribute__((constructor))
static void __srandom(void)
{
	#include <time.h>
	srandom(time(NULL));
}
#endif

static int
getrand(void)
{
	int ret;

#if RANDTYPE == 1
	ret = rand() % MAX;
#elif RANDTYPE == 2
	ret = random() % MAX;
#elif RANDTYPE == 3
	ret = arc4random() % MAX;
#elif RANDTYPE == 4
	ret = arc4random_uniform(MAX);
#endif

	return (ret);
}

int
main(void)
{
	int i, j, k, r;
	int c[MAX];

	initscr();
	memset(c, 0, sizeof(c));

	for (i = 0; i < ITE; i++) {
		r = getrand();
		c[r]++;

		for (j = 0; j < MAX; j++) {
			for (k = 0; k < c[j]; k++)
				mvaddch(j, k, '*');
			mvprintw(j, k, " [%d]", c[j]);
		}

		refresh();
		usleep(500);
	}

	getchar();

	endwin();
	return (0);
}
