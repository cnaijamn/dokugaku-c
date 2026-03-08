// 合字(ごうじ) ; Ligature(リガチャー)
// https://ja.wikipedia.org/wiki/%E5%90%88%E5%AD%97
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#define WLEN	(128)

int
main(void)
{
	//setlocale(LC_CTYPE, "");
	setlocale(LC_CTYPE, "ja_JP.UTF-8");

	printf("%zu\n", mbstowcs(NULL, "abc", 0)); // 3
	printf("%zu\n", mbstowcs(NULL, "あいう", 0)); // 3
	printf("%zu\n", mbstowcs(NULL, "ゟӔæ☃㋿あ漢🙂𠮟𠮷", 0)); // 10

	wchar_t buf[WLEN];

	mbstowcs(buf, "abc", WLEN);
	wprintf(L"%.*ls\n", 3, buf);
	printf(" -> %lu\n", wcslen(buf)); // 3

	mbstowcs(buf, "あいう", WLEN);
	wprintf(L"%.*ls\n", 3, buf);
	printf(" -> %lu\n", wcslen(buf)); // 3

	mbstowcs(buf, "ゟӔæ☃㋿あ漢🙂𠮟𠮷", WLEN);
	wprintf(L"%.*ls\n", 10, buf);
	printf(" -> %lu\n", wcslen(buf)); // 10

	// ラテン文字+結合記号(4コードポイント)
	mbstowcs(buf, "a̲̐́̄", WLEN);
	wprintf(L"%.*ls\n", 5, buf);
	printf(" -> %lu\n", wcslen(buf)); // 5

	// Zalgo風(大量の結合文字)
	mbstowcs(buf, "Z̴̑̾̍̔̍̽́̈́͝", WLEN);
	wprintf(L"%.*ls\n", 11, buf);
	printf(" -> %lu\n", wcslen(buf)); // 11

	// 絵文字(ZWJシーケンス)(4コードポイント)
	mbstowcs(buf, "👩🏽‍💻", WLEN);
	wprintf(L"%.*ls\n", 4, buf);
	printf(" -> %lu\n", wcslen(buf)); // 4

	// レインボーフラッグ(4コードポイント)
	mbstowcs(buf, "🏳️‍🌈", WLEN);
	wprintf(L"%.*ls\n", 4, buf);
	printf(" -> %lu\n", wcslen(buf)); // 4

	// 家族の絵文字(7コードポイント)
	mbstowcs(buf, "👨‍👩‍👧‍👦", WLEN);
	wprintf(L"%.*ls\n", 7, buf);
	printf(" -> %lu\n", wcslen(buf)); // 7

	// ラテン文字の多重結合
	mbstowcs(buf, "ơ̴̓̽̚", WLEN);
	wprintf(L"%.*ls\n", 6, buf);
	printf(" -> %lu\n", wcslen(buf)); // 6

	return (0);
}
