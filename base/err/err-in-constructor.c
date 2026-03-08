#include <stdio.h>
#include <err.h>

__attribute__((constructor))
static void start(void)
{
	// これを表示後終了
	errx(1, "Error occurred");
}

int
main(void)
{
	// ここには何も来ない
	puts("main() start");
	puts("main() end");
	return (0);
}
/*
% ./err-in-constructor
err-in-constructor: Error occurred
% echo $?
1
*/
