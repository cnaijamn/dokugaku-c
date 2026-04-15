/*
% cc -o sample_1 sample_1.c -lm
% ./sample_1
width: 320 / height: 200 / channels: 3
% file /tmp/sample.png
/tmp/sample.png: PNG image data, 320 x 200, 8-bit/color RGB, non-interlaced
% rm -f /tmp/sample.png
*/
#include <err.h>
#include <stdint.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define JPG_FILE	"./sample.jpg"
#define PNG_FILE	"/tmp/sample.png"

int
main(void)
{
	int w, h, ch;
	uint8_t *data;

	// JPGファイルを読み込み
	data = stbi_load(JPG_FILE, &w, &h, &ch, 0);
	if (data == NULL)
		errx(1, "Failed to load JPG: %s", JPG_FILE);
	printf("width: %d / height: %d / channels: %d\n", w, h, ch);

	// PNGファイルに書き込み
	(void)stbi_write_png(PNG_FILE, w, h, ch, data, 0);

	stbi_image_free(data);
	return (0);
}
