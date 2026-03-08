#include <err.h>
#include <errno.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	// stderrに出力
	errno = EFAULT; // "Bad address"
	warn("%s waaaaaaaaan!", argv[0]);

	// xつき
	warnx("%s waaaaaaaaan_x!", argv[0]);

	// cつき
	warnc(EFAULT, "%s waaaaaaaaan_c!", argv[0]);

	// stderrに出力され、終了コード1でexitする
	errx(10, "%s errorrrrrrrr!", argv[0]);

	// ここには来ない
	puts("Don't come here!");
	return 0;
}
/*
% ./sample
sample: ./sample waaaaaaaaan!: Bad address
sample: ./sample waaaaaaaaan_x!
sample: ./sample waaaaaaaaan_c!: Bad address
sample: ./sample errorrrrrrrr!
% echo $?
10
*/
