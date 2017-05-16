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
 * @param images : files
 * @param labels : labels file null if it is training set
 * @return MNIST_image array
 */
int get_image(MNIST_setting * settings, MNIST_image ** images){

}

int main(){
	MNIST_setting * set;

	set = (MNIST_setting *)malloc(sizeof(MNIST_setting));
	get_setting(TRAIN_IMAGES, TRAIN_LABELS, set);
	printf("num_item: %u \nnum_rows: %u \nnum_cols: %u \n", set->num_items, set->num_rows, set->num_cols);
	return 0;
}