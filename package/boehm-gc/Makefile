PROGS=	sample1 sample2 gc+queue nest
MAN=
WARNS=	3

CFLAGS.sample1+=	`pkgconf --cflags --libs bdw-gc`
LDFLAGS.sample1+=	`pkgconf --libs --libs bdw-gc`

CFLAGS.sample2+=	`pkgconf --cflags --libs bdw-gc-threaded`
LDFLAGS.sample2+=	`pkgconf --libs --libs bdw-gc-threaded`

CFLAGS.gc+queue+=	`pkgconf --cflags --libs bdw-gc`
LDFLAGS.gc+queue+=	`pkgconf --libs --libs bdw-gc`

CFLAGS.nest+=	`pkgconf --cflags --libs bdw-gc-threaded`
LDFLAGS.nest+=	`pkgconf --libs --libs bdw-gc-threaded`

.include <bsd.progs.mk>
