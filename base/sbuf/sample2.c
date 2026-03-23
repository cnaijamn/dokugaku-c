// 間違った使い方
#include <stdio.h>
#include <stdlib.h>
#include <sys/sbuf.h>

int
main(void)
{
	struct sbuf sb;

	// sbufで文字列を育てて、文字列だけ取り出し後、
	// sbufを破棄することはできない

	sbuf_new(&sb, NULL, 0, SBUF_AUTOEXTEND);
	sbuf_cat(&sb, "XY");
	sbuf_cat(&sb, "Z");
	sbuf_cat(&sb, "あいうえお");
	sbuf_finish(&sb);

	char *str = sbuf_data(&sb); // sb.s_bufが返される

	sbuf_delete(&sb); // ここでsb.s_bufがfreeされるので、以降、
	                  // strを使うのは危険
	puts(str);
	free(str);

	return (0);
}
