// ref.
// https://github.com/troydhanson/uthash/blob/master/doc/utstring.txt
#include <stdio.h>
#include <utstring.h>

int
main(void)
{
	UT_string *s1, *s2;
	char *str = "sec";

	utstring_new(s1);
	utstring_printf(s1, "hoge ");
	utstring_printf(s1, "fuga %d", 100);
	printf("s1: %s\n", utstring_body(s1));

	utstring_new(s2);
	utstring_bincpy(s2, str, strlen(str));
	printf("s2: %s\n", utstring_body(s2));

	utstring_concat(s1, s2);
	printf("s1: %s\n", utstring_body(s1));

	utstring_free(s2);
	utstring_free(s1);

	return (0);
}
