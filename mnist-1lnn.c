#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "mnist-1lnn.h"



/**
 * @DESC: init one neuran, load images to input and make random weights
 */
Neuron * init_neuron(MNIST_setting * setting){
	Neuron * target;
	int i;
	
	target = (Neuron * )malloc(sizeof(Neuron));

	target->size = setting->num_cols*setting->num_rows;

	target->inputs = (uint8_t *)malloc(sizeof(uint8_t)*target->size);

	target->weights = (double *)malloc(sizeof(double)*target->size);

	for (i = 0; i < target->size; ++i){
		*(target->weights+i) = (double)rand()/(double)RAND_MAX;
	}

	return target;
}

void update_neuron(Neuron * neuron, MNIST_image image){
	int i;
	int pixel_threshold = 150;

	for (i = 0; i < neuron->size; ++i)
	{
		*(neuron->inputs+i) = *(image.pixel + i) < pixel_threshold ? 0 : 1;
	}
}

/**
 * @DESC: init layers
 */
Layer * init_layer(MNIST_setting * setting){
	Layer * target;
	int i;	
	target = (Layer *)malloc(sizeof(Layer));

	for (i = 0; i < 10; ++i)
	{
		target->neurons[i] = *(init_neuron(setting));
	}

	return target;
}

void update_layer(Layer * layer, MNIST_image image){
	int i;

	for (int i = 0; i < 10; ++i)
	{
		update_neuron(layer->neurons+i, image);
	}
	
	layer->label = image.label;

}
/**
 * @DESC: calculate output of a neuron, sigmoid(input * weight)
 */
void predict_prob(Neuron * neuron){
	int i;
	double sum;

	sum = 0;

	for (i = 0; i < neuron->size; ++i)
	{
		sum += *(neuron->inputs + i) * *(neuron->weights + i);
	}
	
	// sum = sum / neuron->size;
	// sum = 1/(1+exp(-sum));

	neuron->output = sum;
}

void predict_probs(Layer * layer){
	int i;

	for (int i = 0; i < 10; ++i)
	{
		predict_prob(layer->neurons+i);
		printf("%lf : %d\n", (layer->neurons+i)->output, i);
	}
}

/**
 * updates
 * @param layer layer of neuran
 * @with output probs, 
 */
void update_weights(Layer * layer){
	int i, j; 
	double error;
	int size = layer->neurons->size;

	printf("real label : %d\n", layer->label);
	for (int i = 0; i < 10; ++i)
	{
		error = (i == layer->label) - (layer->neurons+i)->output;
		
		for (int j = 0; j < size; ++j)
		{
			*((layer->neurons+i)->weights+j) += LEARNING_RATE * error; 
		}
		printf("error : %lf : %d \n", error, i);
	}
}

/**
 * predict what the actual number of the image
 * @param layer
 * @return int
 */
int predict(Layer * layer){
	int i;
	double max;
	double label_selected;

	max = layer->neurons[0].output;
	label_selected = 0;

	for (int i = 1; i < 10; ++i)
	{
		if(max < layer->neurons[i].output){
			max = layer->neurons[i].output;
			label_selected = i;
		}
	}

	return label_selected;
}

/**
 * use static rate to check success rate
 * @param  layer check layer
 * @param  init  if initiation, put init = 1 else 0
 * @return       success rate
 */
double calculate_success_rate(Layer * layer, int init){
	static int num_success;
	static int num_tries;
	if(init){
		num_success = 0;
		num_tries = 0;
		return 0;
	}
	num_tries += 1;

	if(predict(layer) == (int)layer->label){
		num_success += 1;
	}

	return (double)num_success/(double)num_tries;
}

// /**
//  * train layers from image sets and get weights
//  * @param  setting    setting of an MNIST sets
//  * @param  layer      not initiated layer should be given.
//  * @return            success rate of overall process
//  */
double train_layer(MNIST_setting * setting, Layer * layer){
	MNIST_image * images;
	int num_items = setting->num_items;
	int i;
	double success_rate;
	char c;

	images = get_images(setting);
	calculate_success_rate(layer, 1);

	for (i = 0; i < num_items; ++i)
	{
		update_layer(layer, *(images + i));
		predict_probs(layer);
		success_rate = calculate_success_rate(layer, 0);
		update_weights(layer);

		// if(i > 10000){
		// 	scanf("%c", &c);
		// 	getchar();
		// }
	}
	printf("%lf : success_rate \n", success_rate);
	return success_rate;

}

// /**
//  * test with given layer
//  * @param  setting image sets
//  * @param  Layer    trained layer
//  * @return          success rate of overall process
//  */
// double test_layer(MNIST_settings * setting, Layer * layer);









