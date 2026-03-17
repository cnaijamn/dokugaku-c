PROGS=	sample1 sample2
MAN=
WARNS=	3

CFLAGS.sample1+=	`pkgconf --cflags --libs bdw-gc`
LDFLAGS.sample1+=	`pkgconf --libs --libs bdw-gc`

CFLAGS.sample2+=	`pkgconf --cflags --libs bdw-gc-threaded`
LDFLAGS.sample2+=	`pkgconf --libs --libs bdw-gc-threaded`

.include <bsd.progs.mk>
