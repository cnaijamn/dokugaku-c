#include <stdio.h>
#include <mp.h>

int
main(void)
{
	MINT *a, *b, *c;

	a = mp_itom(12345);
	b = mp_itom(6789);
	c = mp_itom(0);

	mp_mult(a, b, c);
	// a x b = c

	printf("result = ");
	mp_mout(c);
	printf("\n");
	// result = 83810205

	mp_mfree(a);
	mp_mfree(b);
	mp_mfree(c);

	return (0);
}
