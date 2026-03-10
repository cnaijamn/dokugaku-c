PROG=	sample1
MAN=
LDADD=

SRCS=	sample1.c

WARNS=	3
CFLAGS+=	`pkgconf --cflags openblas`
LDFLAGS+=	`pkgconf --libs openblas`

.include <bsd.prog.mk>
