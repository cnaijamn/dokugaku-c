// https://github.com/freebsd/freebsd/tree/master/lib/libsbuf
// https://github.com/freebsd/freebsd/blob/master/lib/libsbuf/tests/sbuf_string_test.c
#include <stdio.h>
#include <sys/sbuf.h>

int
main(void)
{
	struct sbuf *sb = sbuf_new_auto();

	sbuf_cat(sb, "XY");
	sbuf_cat(sb, "Z");
	sbuf_finish(sb);
	printf("%s (%zd)\n", sbuf_data(sb), sbuf_len(sb));
	// "XYZ (3)"

	sbuf_cpy(sb, " ABC  ");
	sbuf_finish(sb);
	printf("%s (%zd)\n", sbuf_data(sb), sbuf_len(sb));
	// " ABC   (6)"

	sbuf_trim(sb);
	sbuf_finish(sb);
	printf("%s (%zd)\n", sbuf_data(sb), sbuf_len(sb));
	// " ABC (4)"

	sbuf_cpy(sb, "あいうabc");
	sbuf_finish(sb);
	printf("%s (%zd)\n", sbuf_data(sb), sbuf_len(sb));
	// "あいうabc (12)"

	sbuf_clear(sb);
	sbuf_finish(sb);
	printf("%s (%zd)\n", sbuf_data(sb), sbuf_len(sb));
	// " (0)"

	sbuf_clear(sb);
	sbuf_printf(sb, "%d ", 100);
	sbuf_printf(sb, "%d",  200);
	sbuf_finish(sb);
	printf("%s (%zd)\n", sbuf_data(sb), sbuf_len(sb));
	// "100 200 (7)"

	sbuf_delete(sb);

	return (0);
}
