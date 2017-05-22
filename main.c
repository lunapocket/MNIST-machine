#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "mnist-1lnn.h"

MNIST_image get_image(MNIST_setting *);
int main(){
	MNIST_setting * train_set, *test1_set, * test2_set;
	MNIST_image image;
	MNIST_image * images;
	Layer * layer;
	char c;

	srand(time(NULL));

	train_set = (MNIST_setting *)malloc(sizeof(MNIST_setting));
	test1_set = (MNIST_setting *)malloc(sizeof(MNIST_setting));
	test2_set = (MNIST_setting *)malloc(sizeof(MNIST_setting));

	get_setting(TRAIN_IMAGES, TRAIN_LABELS, train_set);

	printf("num_item: %u \nnum_rows: %u \nnum_cols: %u \n", train_set->num_items, train_set->num_rows, train_set->num_cols);
	
	layer = init_layer(train_set);
	printf("=======training....\n");
	train_layer(train_set, layer);

	printf("=======testing train set\n");
	get_setting(TRAIN_IMAGES, TRAIN_LABELS, test1_set);
	test_layer(test1_set, layer);

	printf("=======testing test set\n");
	get_setting(TEST_IMAGES, TEST_LABELS, test2_set);
	test_layer(test2_set, layer);




	// while(1){
	// 	printf("label: %u \n", images->label);
	// 	images = images + 1;
	// }
	// while(1){
	// 	image = get_image(set);
	// 	printf("pixel: %u \nlabel: %u\n",image.pixel[0], image.label);
	// 	print_image(set, image);
	// 	scanf("%c", &c);
	// 	getchar();
	// }
}
