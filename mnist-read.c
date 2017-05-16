/**
 * desc : read mnist-formatted file
 */

#include <stdio.h>
#include <stdint.h>

#include "mnist-read.h"

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
FILE * get_setting(char * path_images, char * path_labels, MNIST_setting * settings){
	FILE * fp; 
	if( (fp = fopen(path_images, "rb") ) == NULL )
		perror("file open failed");

	settings->num_items = 0;
	settings->num_rows = 0;
	settings->num_cols = 0;
	
	fread(NULL, 4, 1, fp); //magic number
	fread(settings->num_items, 4, 1, fp); //number of images
	fread(settings->num_items)
	
	return fp;
}


/**
 * @param images : files
 * @param labels : labels file null if it is training set
 * @return MNIST_image array
 */
int get_image(FILE * fp_images, char * path_labels, MNIST_image ** images){

}