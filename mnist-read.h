/**
 * desc : read mnist-formatted file
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TRAIN_LABELS "data/train-labels.idx1-ubyte"
#define TRAIN_IMAGES "data/train-images.idx3-ubyte"
#define TEST_LABELS "data/t10k-labels.idx1-ubyte"
#define	TEST_IMAGES "data/t10k-images.idx3-ubyte"

/**
 * structure for MNIST_settings and images
 */
typedef struct MNIST_setting {
	FILE * fp_images;
	FILE * fp_labels;
	uint32_t num_items;
	uint32_t num_rows;
	uint32_t num_cols;
} MNIST_setting;

typedef struct MNIST_image {
	uint8_t * pixel;
	uint8_t label;
} MNIST_image ;

/**
 * desc : get settings(items, rows, cols) from file
 * @return FILE pointer of images
 */
void get_setting(char * path_images, char * path_labels, MNIST_setting * settings);

/**
 * @param images : files 
 * @param labels : labels file null if it is training set : path
 * @return int - 1: success, 0: fail, MNIST_image array
 */
MNIST_image * get_images(MNIST_setting * settings);

/**
 * print mnist image
 */

void print_image(MNIST_setting * settings, MNIST_image image);