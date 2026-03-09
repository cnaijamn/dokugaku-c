// jdate / ndaysj : ユリウス暦(Julian calendar)
// ユリウス通日(天文学用、JD、Julian day)とは違うので注意！
#include <calendar.h>
#include <stdio.h>

int
main(void)
{
	int n;
	struct date dt;

	// B.C.1年(西暦0年)3月1日を起点(0)として、
	// 指定された日までの経過日数を返す
	n = ndaysj(&(struct date){
	    .y = 0,
	    .m = 3,
	    .d = 1,
	});
	printf("ndaysj -> %d\n", n);
	// ndaysj -> 0

	(void)jdate(n, &dt);
	printf("jdate -> %04d-%02d-%02d\n", dt.y, dt.m, dt.d);
	// jdate -> 0000-03-01

	return (0);
}
