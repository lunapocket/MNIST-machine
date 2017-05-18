#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mnist-1lnn.h"

int main(){
	MNIST_setting * set;
	MNIST_image image;
	MNIST_image * images;
	Layer * layer;
	char c;

	srand(time(NULL));

	set = (MNIST_setting *)malloc(sizeof(MNIST_setting));
	get_setting(TRAIN_IMAGES, TRAIN_LABELS, set);

	printf("num_item: %u \nnum_rows: %u \nnum_cols: %u \n", set->num_items, set->num_rows, set->num_cols);


	layer = init_layer(set);
	train_layer(set, layer);



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