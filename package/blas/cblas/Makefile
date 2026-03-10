PROG=	sample1
MAN=
LDADD=

SRCS=	sample1.c

WARNS=	3
CFLAGS+=	`pkgconf --cflags cblas`
LDFLAGS+=	`pkgconf --libs cblas`

.include <bsd.prog.mk>
