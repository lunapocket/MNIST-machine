/**
 * desc : read mnist-formatted file
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> //malloc for test
#include "mnist-read.h"

#pragma GCC diagnostic ignored "-Wwrite-strings"

/**
 * SWAP bytes from MNIST
 */

uint32_t swap_bytes(uint32_t original){
	uint32_t b[4];

	b[0] = (original & 0xFF) << 24;
	b[1] = (original & 0xFF00) << 8;
	b[2] = (original & 0xFF0000) >> 8;
	b[3] = (original & 0xFF000000) >> 24;

	return (b[0] | b[1] | b[2] | b[3]);
}

/**
 * desc : get settings(items, rows, cols) from file
 */
void get_setting(char * path_images, char * path_labels, MNIST_setting * settings){

	if( (settings->fp_images = fopen(path_images, "rb") ) == NULL )
		perror("file open failed");

	if( (settings->fp_labels = fopen(path_labels, "rb") ) == NULL )
		perror("file open failed");

	settings->num_items = 0;
	settings->num_rows = 0;
	settings->num_cols = 0;
	
	fseek(settings->fp_images, 4, SEEK_CUR);
	fseek(settings->fp_labels, 8, SEEK_SET);

	fread(&settings->num_items, 4, 1, settings->fp_images); //number of images
	fread(&settings->num_rows, 4, 1, settings->fp_images); //number of rows
	fread(&settings->num_cols, 4, 1, settings->fp_images); //number of cols

	settings->num_items = swap_bytes(settings->num_items);
	settings->num_cols = swap_bytes(settings->num_cols);
	settings->num_rows = swap_bytes(settings->num_rows);
	return;
}


/**
 * DESC : get image, file pointer moves
 */
MNIST_image get_image(MNIST_setting * settings){
	MNIST_image image;
	int image_size;
	image_size = sizeof(uint8_t)*settings->num_rows*settings->num_cols;

	image.pixel = (uint8_t *)alloca(image_size);

	fread(image.pixel, image_size, 1, settings->fp_images);
	fread(&image.label, 1, 1, settings->fp_labels);

	return image;
}

void print_image(MNIST_setting * settings, MNIST_image image){
	int i, j;
	uint8_t pixel_threshold = 1;
	uint8_t * pixel = image.pixel;

	for (i = 0; i < settings->num_rows; i++)
	{
		for (j = 0; j < settings->num_cols; j++)
		{
			if(*pixel < pixel_threshold)
				printf(".");
			else
				printf("*");
			pixel = pixel+1;
		}
		printf("\n");
	}
}


int get_images(MNIST_setting * settings, MNIST_image ** images){

}

int main(){
	MNIST_setting * set;
	MNIST_image image;
	char c;

	set = (MNIST_setting *)malloc(sizeof(MNIST_setting));
	get_setting(TEST_IMAGES, TEST_LABELS, set);


	printf("num_item: %u \nnum_rows: %u \nnum_cols: %u \n", set->num_items, set->num_rows, set->num_cols);
	while(1){
		image = get_image(set);
		printf("pixel: %u \nlabel: %u\n",image.pixel[0], image.label);
		print_image(set, image);
		scanf("%c", &c);
		getchar();
	}


	return 0;
}