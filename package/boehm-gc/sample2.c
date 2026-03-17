// GC_gcollectの確認
#include <gc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void
finalizer_0(GC_PTR obj, GC_PTR client_data)
{
	printf("FINALIZER_0 called: %zu\n", (size_t)client_data);
	fflush(stdout);
}

static void
finalizer(GC_PTR obj, GC_PTR client_data)
{
	putchar('.');
	fflush(stdout);
}

int
main(void)
{
	char *str, *str_z;

	GC_INIT();

	str = GC_MALLOC_ATOMIC(8);
	GC_REGISTER_FINALIZER(str, finalizer_0, (GC_PTR)0, NULL, NULL);
	strcpy(str, "abcdefg");
	str_z = str + 3; // strをstr_zに
	GC_REGISTER_FINALIZER(str_z, finalizer_0, (GC_PTR)0, NULL, NULL);
	str = NULL;
	// ここでfinalizer0は呼ばれない。strはGC対象にならない

	for (size_t i = 1; i <= 1000; ++i) {
		usleep(100);
		str = GC_MALLOC_ATOMIC(8); // strを使いまわし
		GC_REGISTER_FINALIZER(str, finalizer, (GC_PTR)i, NULL, NULL);
		if (i % 100 == 0) {
			printf("\nGC_gcollect %zu\n", i);
			fflush(stdout);
#if 1
			GC_gcollect();
#endif
		}
	}

	puts("--------------------------------------------------");
	puts(str_z); // "defg"
	fflush(stdout);
	str_z = NULL;
	GC_gcollect(); // ここで無事最初のstrが解放される(finalizerが呼ばれる)

	return (0);
}
